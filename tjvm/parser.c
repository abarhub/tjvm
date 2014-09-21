//#include "StdAfx.h"

//#include <stdint.h>
#include "jclasse.h"
#include <stdio.h>
#include <stdlib.h>
//#include <fcntl.h>
#include <string.h>
#include <assert.h>

#include "outils.h"
#include "pfile.h"
#include "jerror.h"
#include "parser.h"

//#define BUFFER_SIZE (1024*1024)
#define BUFFER_SIZE (1024)

int const_equals(JCLASS* classe,uint16_t val,JSTR *buf)
{
	CP_INFO *cp;
	assert(classe!=NULL);
	assert(buf!=NULL);
	assert(val>0);
	//assert(val<=classe->constant_pool_count+1);
	cp=&(classe->constant_pool[val-1]);
	//if(strncmp(cp->buf,buf,cp->len)==0)
	if(jstrEquals(cp->str,buf))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void read_attr(FILEBUFFER *file,ATTRIBUTE_INFO *attr,JCLASS* classe,JENV *env)
{
	unsigned short name;
	unsigned int len;
	char *buf;
	JSTR *nom_code;
	assert(file!=NULL);
	assert(attr!=NULL);
	assert(classe!=NULL);
	assert(env!=NULL);
	name=read_uint16(file,env);
	len=read_uint32(file,env);
	printf("attr:name=%d,len=%d\n",name,len);
	attr->attribute_name_index=name;
	attr->attribute_length=len;
	if(len>0)
	{
		//attr->info=(char*)calloc(len,sizeof(char));
		if(const_equals(classe,attr->attribute_name_index,createJStrC("Code")))
		{
			uint16_t max_stack,max_locals,exception_table_length;
			uint32_t code_length;
			uint8_t *code;
			CODE_ATTRIBUTE *code_attr;
			EXCEPTION_TABLET *except;
			int i,len2,j;

			len2=14;
			attr->type_attribut=CodeAttr;
			max_stack=read_uint16(file,env);
			max_locals=read_uint16(file,env);
			code_length=read_uint32(file,env);
			code_attr=(CODE_ATTRIBUTE*)calloc(1,sizeof(CODE_ATTRIBUTE));
			attr->code=code_attr;
			code_attr->max_locals=max_locals;
			code_attr->max_stack=max_stack;
			code_attr->code_length=code_length;
			if(code_length>0)
			{
				code=(uint8_t*)read_char(file,code_length,env);
				code_attr->code=code;
				len2+=code_length;
			}
			exception_table_length=read_uint16(file,env);
			len2+=2;
			code_attr->exception_table_length=exception_table_length;
			if(exception_table_length>0)
			{
				code_attr->exception_table=(EXCEPTION_TABLET *)calloc(exception_table_length,sizeof(EXCEPTION_TABLET));
				except=code_attr->exception_table;
				for(i=0;i<exception_table_length;i++)
				{
					except->start_pc=read_uint16(file,env);
					except->end_pc=read_uint16(file,env);
					except->handler_pc=read_uint16(file,env);
					except->catch_type=read_uint16(file,env);
					except++;
					len2+=8;
				}
			}
			code_attr->attributes_count=read_uint16(file,env);
			len2+=2;
			if(code_attr->attributes_count>0)
			{
				code_attr->attributes=(ATTRIBUTE_INFO*)calloc(code_attr->attributes_count,sizeof(ATTRIBUTE_INFO));
				for(j=0;j<code_attr->attributes_count;j++)
				{
					read_attr(file,&(code_attr->attributes[j]),classe,env);
					len2+=code_attr->attributes[j].attribute_length;
				}
			}
			printf("attr_code:max_stack=%d,max_locals=%d,code_length=%d,exception_table_length=%d,attributes_count=%d\n",max_stack,max_locals,code_length,exception_table_length,code_attr->attributes_count);
			assert(len==len2);
		}
		else
		{
			attr->info=read_char(file,len,env);
			attr->type_attribut=AutreAttr;
			printf("attr_autre\n");
		}
	}
}

JCLASS* lecture(char *fichier,JENV *env)
{
	char *buffer/*[BUFFER_SIZE+1]*/;
	//FILE *fp;
	size_t len,len_buff;
	char buf[100];
	unsigned int header;
	unsigned int *pint;
	uint16_t *pshort,version_mineur,version_majeur,nb_const,*pos,acces_flag,this_class,parent_class,nb_interface,nb_fields,nb_methods,nb_attributs;
	unsigned char *pchar;
	unsigned long *plong;
	size_t bytes_read;
	int i,no;
	FILEBUFFER *file;
	JCLASS *res=NULL;

	assert(env!=NULL);

	len_buff=BUFFER_SIZE+20;

	//buffer=(unsigned char *)calloc(len_buff,1);

	/*fp=fopen(fichier, "rb");
	if(fp==NULL)
	{
		perror("Error in opening file");
		return NULL;
	}*/
	file=readFile(fichier,env);

	if(file==NULL)
	{
		//printf("Error in reading from file : %s\n",fichier);
		if(!tjvm_env_is_error(env))
		{
			tjvm_env_add_error_c(env,"Error in reading from file");
		}
		return NULL;
	}

	/* Read in 256 8-bit numbers into the buffer */
	bytes_read = 0;
	//len=1024*1024;
	//len=1024;
	len=800;
	//bytes_read = fread(buffer, len, 1, fp);
	//bytes_read = fread(buffer, 1,len, fp);
	bytes_read=file->len;
	buffer=file->buf;
	//bytes_read = fread(&buf, sizeof(buf), 1, fp);
	
	header=0;
	if(bytes_read>=10)
	{
		header=read_uint32(file,env);
		if(!tjvm_env_is_error(env))
		{
			version_mineur=read_uint16(file,env);
		}
		if(!tjvm_env_is_error(env))
		{
			version_majeur=read_uint16(file,env);
		}
		if(!tjvm_env_is_error(env))
		{
			nb_const=read_uint16(file,env);
		}
	}

	printf("read=%d,%0X,%d,%d,%d!\n",bytes_read,header,(int)version_mineur,(int)version_majeur,(int)nb_const);

	res=(JCLASS*)calloc(1,sizeof(JCLASS));
	if(res==NULL)
	{
		tjvm_env_add_error_c(env,"Error in allocation");
		return NULL;
	}
	res->magic=header;
	res->minor_version=version_mineur;
	res->major_version=version_majeur;
	res->constant_pool_count=nb_const;

	if(!tjvm_env_is_error(env))
	{
		if(nb_const>0)
		{
			CP_INFO *p;
			res->constant_pool=(CP_INFO*)calloc(nb_const,sizeof(CP_INFO));
			p=res->constant_pool;
			no=1;
			for(i=0;i<nb_const-1;i++)
			{
				int code,len2,val;
				uint32_t val_int32;
				uint64_t val_int64;
				uint16_t val_int16;

				code=read_uint8(file,env);
				p->tag=code;
				if(code==CONSTANT_Utf8)
				{
					char* buf0;
					len2=read_uint16(file,env);
					buf0=read_char(file,len2,env);
					//printf("%d) Code string=%d[%d](%s)\n",no,code,len2,buf0);
					//p->len=len2;
					//p->buf=buf0;
					p->str=createJStr(buf0,len2,EUTF8J);
					printf("%d) Code string=%d[%d](",no,code,len2);
					jstrprint(p->str);
					printf(")\n");
					free(buf0);
					buf0=NULL;
					no++;
				}
				else if(code==CONSTANT_Integer||code==CONSTANT_Float||code==CONSTANT_Fieldref||code==CONSTANT_Methodref||code==CONSTANT_InterfaceMethodref||code==CONSTANT_NameAndType)
				{
					val_int32=read_uint32(file,env);
					printf("%d) Code 32=%d(%d)\n",no,code,val_int32);
					p->val_int=val_int32;
					no++;
				}
				else if(code==CONSTANT_Long||code==CONSTANT_Double)
				{
					val_int64=read_uint64(file,env);
					printf("%d) Code 64=%d\n",no,code);
					p->val_long=val_int64;
					no++;
				}
				else if(code==CONSTANT_Class||code==CONSTANT_String)
				{
					val_int16=read_uint16(file,env);
					printf("%d) Code 16=%d(%d)\n",no,code,val_int16);
					p->index_class_ref=val_int16;
					no++;
				}
				else
				{
					printf("%d) Code invalide=%d\n",no,code);
					break;
				}
				p++;
			}
		}
	}

	if(!tjvm_env_is_error(env))
	{
		acces_flag=read_uint16(file,env);
		this_class=read_uint16(file,env);
		parent_class=read_uint16(file,env);
		nb_interface=read_uint16(file,env);
		printf("acces=%d,this=%d,parent=%d,nb_interface=%d\n",acces_flag,this_class,parent_class,nb_interface);
		res->access_flags=acces_flag;
		res->this_class=this_class;
		res->super_class=parent_class;
		res->interfaces_count=nb_interface;

		if(nb_interface>0)
		{
			res->interfaces=(uint16_t*)calloc(nb_interface,sizeof(uint16_t));
			for(i=0;i<nb_interface;i++)
			{
				unsigned short no_interf;
				no_interf=read_uint16(file,env);
				printf("%d) Interface=%d\n",i,no_interf);
				res->interfaces[i]=no_interf;
			}
		}
	}

	if(!tjvm_env_is_error(env))
	{
		nb_fields=read_uint16(file,env);
		printf("nb_fields=%d\n",nb_fields);
		res->fields_count=nb_fields;
		if(nb_fields>0)
		{
			res->fields=(FIELD_INFO*)calloc(nb_fields,sizeof(FIELD_INFO));
			for(i=0;i<nb_fields;i++)
			{
				unsigned short acc_flag,name,descriptor,nb_attr,j;
				acc_flag=read_uint16(file,env);
				name=read_uint16(file,env);
				descriptor=read_uint16(file,env);
				nb_attr=read_uint16(file,env);
				printf("%d) fields: acces=%d,nom=%d,descriptor=%d,nb_attr=%d\n",i,acc_flag,name,descriptor,nb_attr);
				res->fields[i].access_flags=acc_flag;
				res->fields[i].name_index=name;
				res->fields[i].descriptor_index=descriptor;
				res->fields[i].attributes_count=nb_attr;
				if(nb_attr>0)
				{
					res->fields[i].attributes=(ATTRIBUTE_INFO*)calloc(nb_attr,sizeof(ATTRIBUTE_INFO));
					for(j=0;j<nb_attr;j++)
					{
						read_attr(file,&(res->fields[i].attributes[j]),res,env);
					}
				}
			}
		}
	}
	
	if(!tjvm_env_is_error(env))
	{
		nb_methods=read_uint16(file,env);
		printf("nb_methods=%d\n",nb_methods);
		res->methods_count=nb_methods;
		if(nb_methods>0)
		{// TODO: a finir
			res->methods=(JMETHOD_INFO*)calloc(nb_methods,sizeof(JMETHOD_INFO));
			for(i=0;i<nb_methods;i++)
			{
				unsigned short acc_flag,name,descriptor,nb_attr,j;
				acc_flag=read_uint16(file,env);
				name=read_uint16(file,env);
				descriptor=read_uint16(file,env);
				nb_attr=read_uint16(file,env);
				printf("%d) methode: acces=%d,nom=%d,descriptor=%d,nb_attr=%d\n",i,acc_flag,name,descriptor,nb_attr);
				res->methods[i].access_flags=acc_flag;
				res->methods[i].name_index=name;
				res->methods[i].descriptor_index=descriptor;
				res->methods[i].attributes_count=nb_attr;
				if(nb_attr>0)
				{
					res->methods[i].attributes=(ATTRIBUTE_INFO*)calloc(nb_attr,sizeof(ATTRIBUTE_INFO));
					for(j=0;j<nb_attr;j++)
					{
						read_attr(file,&(res->methods[i].attributes[j]),res,env);
					}
				}
			}
		}
	}

	if(!tjvm_env_is_error(env))
	{
		nb_attributs=read_uint16(file,env);
		printf("nb_attributs=%d\n",nb_attributs);
		res->attributes_count=nb_attributs;
		if(nb_attributs>0)
		{// TODO: a finir
			res->attributes=(ATTRIBUTE_INFO*)calloc(nb_attributs,sizeof(ATTRIBUTE_INFO));
			for(i=0;i<nb_attributs;i++)
			{
				read_attr(file,&(res->attributes[i]),res,env);
			}
		}
	}

	//free(buffer);
	//fclose(fp);

	if(tjvm_env_is_error(env))
	{
		return NULL;
	}
	else
	{
		return res;
	}
}


