#include<stdio.h>
#include<assert.h>
//#include <stdint.h>
#include<malloc.h>
#include<string.h>

#include "jclasse.h"
#include "opcode2.h"
#include "context.h"
#include "opcode.h"
#include "jenv.h"


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

/*static void affiche_frame(JFRAME *frame)
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
}*/

JFRAME *create_jframe(JCLASS *classe,CODE_ATTRIBUTE *code)
{
	JFRAME *frame;

	assert(classe!=NULL);
	assert(code!=NULL);

	frame=(JFRAME*)calloc(1,sizeof(JFRAME));
	frame->classe=classe;
	frame->methode=code;
	frame->nb_var_local=code->max_locals;
	if(frame->nb_var_local>0)
	{
		//frame->var_local=(uint32_t*)calloc(frame->nb_var_local,sizeof(uint32_t));
		frame->local_val=(TYPEVALSTACK*)calloc(frame->nb_var_local,sizeof(TYPEVALSTACK));
	}
	frame->nb_stack=code->max_stack;
	if(frame->nb_stack>0)
	{
		//frame->stack=(uint32_t*)calloc(frame->nb_stack,sizeof(uint32_t));
		frame->stack_val=(TYPEVALSTACK*)calloc(frame->nb_stack,sizeof(TYPEVALSTACK));
	}
	frame->len_code=code->code_length;
	frame->code=code->code;
	frame->pos_code=0;
	frame->pos_stack=0;

	return frame;
}

void exec(JCLASS *classe,JMETHOD_INFO *tmp,JENV *env)
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
	assert(env!=NULL);

	if(tmp->attributes_count==0)
	{
		//printf("error: pas de code");
		tjvm_env_add_error_c(env,"Pas de code");
	}
	else
	{
		context=new_context_run(classe,tmp,env);
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
		frame=create_jframe(classe,code);
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

void run2(JCLASS *classe,JENV *env)
{
	JMETHOD_INFO *tmp;
	assert(classe!=NULL);
	assert(env!=NULL);

	tmp=trouve_methode(classe,createJStrC("test1"));
	assert(tmp!=NULL);
	printf("methode:%d\n",tmp->name_index);
	exec(classe,tmp,env);
	return;
}