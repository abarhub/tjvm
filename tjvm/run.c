#include<stdio.h>
#include<assert.h>
//#include <stdint.h>
#include<malloc.h>
#include<string.h>

#include "jclasse.h"
#include "opcode2.h"
#include "context.h"
#include "opcode.h"


int debug=1;

/*
constante est entre 1 et nb constantes
*/
static JSTR *donne_constante(JCLASS *classe,int no_constante)
{
	int i;
	char *tmp;
	CP_INFO *tmp2;
	assert(classe!=NULL);
	assert(no_constante>0);
	assert(no_constante<=classe->constant_pool_count);
	if(classe->constant_pool_count<=0)
	{
		return NULL;
	}
	else if(classe->constant_pool_count<=no_constante)
	{
		return NULL;
	}
	else
	{
		tmp2=&((classe->constant_pool)[no_constante-1]);
		if(tmp2==NULL)
		{
			return NULL;
		}
		else if(tmp2->tag!=CONSTANT_Utf8)
		{
			return NULL;
		}
		else
		{
			/*tmp=(char*)calloc(tmp2->len+1,sizeof(char));
			strncpy(tmp,tmp2->buf,tmp2->len);
			return tmp;*/
			return tmp2->str;
		}
	}
}

static int est_constante(JCLASS *classe,JSTR *nom,uint16_t name_index)
{
	JSTR *buf;
	int res;
	assert(classe!=NULL);
	assert(nom!=NULL);
	assert(name_index>0);

	buf=donne_constante(classe,name_index);
	if(buf==NULL)
	{
		return 0;
	}
	else
	{
		//if(strcmp(buf,nom)==0)
		if(jstrEquals(buf,nom))
		{
			res=1;
		}
		else
		{
			res=0;
		}
		//free(buf);
		return res;
	}
}

static JMETHOD_INFO * trouve_methode(JCLASS *classe,JSTR *nom_methode)
{
	JMETHOD_INFO *tmp;
	int i,index;
	char *tmp2;
	assert(classe!=NULL);
	assert(nom_methode!=NULL);
	if(classe->methods_count<=0)
	{
		return NULL;
	}
	else
	{
		i=0;
		tmp=classe->methods;
		for(i=0;i<classe->methods_count;i++)
		{
			index=tmp->name_index;
			//tmp2=donne_constante(classe,index);
			//assert(tmp2!=NULL);
			if(est_constante(classe,nom_methode,index))
			{
				return tmp;
			}
			tmp++;
		}
	}
	return NULL;
}

static void affiche_frame(JFRAME *frame)
{
	if(frame==NULL)
	{
		printf("Frame vide\n");
	}
	else
	{
		int nb_var_max,nb_stack_max,pos_stack,pos_code;
		int i;
		nb_var_max=frame->nb_var_local;
		nb_stack_max=frame->nb_stack;
		pos_stack=frame->pos_stack;
		pos_code=frame->pos_code;
		printf("var:");
		for(i=0;i<nb_var_max;i++)
		{
			printf("%d ",frame->var_local[i]);
		}
		printf("\n");
		printf("stack (%d):",pos_stack);
		for(i=0;i<nb_stack_max;i++)
		{
			printf("%d ",frame->stack[i]);
		}
		printf("\n");
	}
}

#define ICONST_0 0x03
#define ICONST_1 0x04
#define ICONST_2 0x05
#define ICONST_3 0x06
#define ICONST_4 0x07
#define ICONST_5 0x08
#define ISTORE_0 0x3B
#define ISTORE_1 0x3C
#define ISTORE_2 0x3D
#define ISTORE_3 0x3E
#define ILOAD_0 0x1A
#define ILOAD_1 0x1B
#define ILOAD_2 0x1C
#define ILOAD_3 0x1D
#define IADD 0x60
#define RETURN 0xB1

static void push_stack_val(JFRAME *frame,int32_t val)
{
	assert(frame!=NULL);
	assert(frame->pos_stack>=0);
	assert(frame->pos_stack<frame->nb_stack);
	frame->stack[frame->pos_stack]=val;
	frame->pos_stack++;
}

static int32_t pop_stack(JFRAME *frame)
{
	int32_t val;
	assert(frame!=NULL);
	assert(frame->pos_stack>0);
	val=frame->stack[frame->pos_stack-1];
	frame->pos_stack--;
	return val;
}

static void set_var_local(JFRAME *frame,uint16_t no_var,uint32_t val)
{
	assert(frame!=NULL);
	assert(frame->nb_var_local>0);
	assert(no_var>=0);
	assert(no_var<frame->nb_var_local);
	frame->var_local[no_var]=val;
}

static uint32_t get_var_local(JFRAME *frame,uint16_t no_var)
{
	uint32_t val;
	assert(frame!=NULL);
	assert(frame->nb_var_local>=0);
	assert(no_var>=0);
	assert(no_var<frame->nb_var_local);
	val=frame->var_local[no_var];
	return val;
}

void exec(JCLASS *classe,JMETHOD_INFO *tmp)
{
	ATTRIBUTE_INFO *attr,*attr_code;
	int i,pos;
	char *nom;
	CODE_ATTRIBUTE *code=NULL;
	uint8_t *code_bin=NULL,c;
	JFRAME *frame=NULL;
	JCONTEXT *context;

	assert(classe!=NULL);
	assert(tmp!=NULL);
	if(tmp->attributes_count==0)
	{
		printf("error: pas de code");
	}
	else
	{
		context=new_context_run(classe,tmp);
		attr_code=NULL;
		attr=tmp->attributes;
		for(i=0;i<tmp->attributes_count;i++)
		{
			//if(est_constante(classe,"Code",attr->
			if(attr->type_attribut==CodeAttr)
			{
				attr_code=attr;
				break;
			}
		}
		assert(attr_code!=NULL);
		code=attr_code->code;
		assert(code!=NULL);
		code_bin=code->code;
		assert(code_bin!=NULL);
		frame=(JFRAME*)calloc(1,sizeof(JFRAME));
		frame->classe=classe;
		frame->methode=code;
		frame->nb_var_local=code->max_locals;
		if(frame->nb_var_local>0)
		{
			frame->var_local=(uint32_t*)calloc(frame->nb_var_local,sizeof(uint32_t));
		}
		frame->nb_stack=code->max_stack;
		if(frame->nb_stack>0)
		{
			frame->stack=(uint32_t*)calloc(frame->nb_stack,sizeof(uint32_t));
		}
		frame->len_code=code->code_length;
		frame->code=code->code;
		frame->pos_code=0;
		frame->pos_stack=0;
		context->frame=frame;

		if(debug)
		{
			printf("debut code0\n");
			for(i=0;i<code->code_length;i++)
			{
				printf("%Xd\n",code_bin[i]);
			}
			printf("fin code0\n");
			affiche_opcode(code_bin,code->code_length);
			printf("frame debut:\n");
			affiche_frame(frame);
		}
		execute(context);
	}
}

void run2(JCLASS *classe)
{
	JMETHOD_INFO *tmp;
	assert(classe!=NULL);

	tmp=trouve_methode(classe,createJStrC("test1"));
	assert(tmp!=NULL);
	printf("methode:%d\n",tmp->name_index);
	exec(classe,tmp);
	return;
}