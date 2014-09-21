#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <malloc.h>

#include "opcode.h"
#include "opcode2.h"

void affiche_opcode(uint8_t *buf,int len);

static void push_stack_val(JFRAME *frame,int32_t val)
{
	assert(frame!=NULL);
	assert(frame->pos_stack>=0);
	assert(frame->pos_stack<frame->nb_stack);
	frame->stack[frame->pos_stack]=val;
	frame->stack_val[frame->pos_stack].type_val=EInt32Stack;
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

void INSTR_LOAD(JCONTEXT *context,ETYPE type,int index_local,int param)
{
	assert(context!=NULL);

	if(type==TINT)
	{
		if(param==0)
		{
			uint16_t no_var;
			uint32_t val=0;
			no_var=index_local;
			assert(no_var>=0&&no_var<=3);
			val=get_var_local(context->frame,no_var);
			push_stack_val(context->frame,val);
			//INCR_INSTR(context);
		}
		else
		{
			uint8_t no;
			uint16_t no_var;
			uint32_t val=0;
			//INCR_INSTR(context);
			//no_var=DONNE_INSTR_SUIVANTE(context);
			no_var=context->code_courant[0];
			assert(no_var>=0);
			val=get_var_local(context->frame,no_var);
			push_stack_val(context->frame,val);
			//INCR_INSTR(context);
		}
	}
	else
	{
		assert(1==0);
	}

	
}

void INSTR_STORE(JCONTEXT *context,ETYPE type,int index_local,int param)
{
	int32_t val;
	uint16_t no_var;
	assert(context!=NULL);
		
	val=pop_stack(context->frame);
	if(type==TINT)
	{
		if(param==0)
		{
			no_var=index_local;
			assert(no_var>=0&&no_var<=3);
			set_var_local(context->frame,no_var,val);
			//INCR_INSTR(context);
		}
		else
		{
			//INCR_INSTR(context);
			//no_var=DONNE_INSTR_SUIVANTE(context);
			no_var=context->code_courant[0];
			assert(no_var>=0);
			set_var_local(context->frame,no_var,val);
			//INCR_INSTR(context);
		}
	}
	else
	{
		assert(1==0);
	}
}

void INSTR_CONST(JCONTEXT *context,ETYPE type,int val,int param)
{
	//uint32_t val0=0;
	int32_t val0=0;

	assert(context!=NULL);

	if(type==TINT)
	{
		if(param==0)
		{
			val0=val;
			assert(val0>=-1&&val0<=5);
			push_stack_val(context->frame,val0);
			//INCR_INSTR(context);
		}
		else
		{
			//INCR_INSTR(context);
			//val0=DONNE_INSTR_SUIVANTE(context);
			val0=context->code_courant[0];
			push_stack_val(context->frame,val0);
			//INCR_INSTR(context);
		}
	}
	else if(type==TBYTE)
	{
		if(param==1)
		{
			//INCR_INSTR(context);
			//val0=DONNE_INSTR_SUIVANTE(context);
			val0=context->code_courant[0];
			push_stack_val(context->frame,val0);
			//INCR_INSTR(context);
		}
		else
		{
			assert(1==0);
		}
	}
	else
	{
		assert(1==0);
	}

}

void INSTR_RETURN(JCONTEXT *context,ETYPE type)
{
	assert(context!=NULL);
	assert(type==TVOID);
	assert(context->frame->pos_stack==0);
	context->fini=1;
	//INCR_INSTR(context);
}

void INSTR_OPBIN(JCONTEXT *context,ETYPE type,EOPERATEUR operateur)
{
	int32_t val,val2;
	if(type==TINT)
	{
		val=pop_stack(context->frame);
		val2=pop_stack(context->frame);
		switch(operateur)
		{
		case TADD:
			val+=val2;
			break;
		case TSUB:
			val-=val2;
			break;
		case TMULT:
			val*=val2;
			break;
		case TDIV:
			assert(val2!=0);
			val/=val2;
			break;
		case TAND:
			val=val&&val2;
			break;
		case TOR:
			val=val||val2;
			break;
		case TXOR:
			val=val ^ val2;
			break;
		case TSHR:
			val=val>>val2;
			break;
		case TSHL:
			val=val<<val2;
			break;
		case TREM:
			val=val%val2;
			break;
		case TUSHR:
			{// https://en.wikipedia.org/wiki/Logical_shift
				uint32_t val0,val3;
				val0=val;
				val3=val2;
				val=val0>>val3;
			}
			break;
		default:
			assert(1==0);
		}
		push_stack_val(context->frame,val);
	}
	else
	{
		assert(1==0);
	}
	//INCR_INSTR(context);
}

void INSTR_AUTRE(JCONTEXT *context)
{
	assert(context!=NULL);

	assert(1==0);
}

void INSTR_ITERATION(JCONTEXT *context)
{
	assert(context!=NULL);

	printf("instr no %d\n",context->frame->pos_code);
	affiche_opcode(context->frame->code+context->frame->pos_code,1);
	affiche_frame(context->frame);
}

void INSTR_DEBUT(JCONTEXT *context)
{
	assert(context!=NULL);
	printf("Debut\n");
}

void INSTR_FIN(JCONTEXT *context)
{
	assert(context!=NULL);
	printf("Fin\n");
}

int EST_FINI(JCONTEXT *context)
{
	assert(context!=NULL);
	return context->fini||tjvm_env_is_error(context->env);
}

uint8_t DONNE_INSTR_SUIVANTE(JCONTEXT *context)
{
	size_t pos;
	JFRAME *frame;
	assert(context!=NULL);
	frame=context->frame;
	assert(frame!=NULL);
	pos=frame->pos_code;
	assert(pos>=0);
	assert(pos<frame->len_code);
	return frame->code[pos];
}

void INCR_INSTR(JCONTEXT *context)
{
	size_t pos;
	JFRAME *frame;
	assert(context!=NULL);
	frame=context->frame;
	assert(frame!=NULL);
	pos=frame->pos_code;
	assert(pos>=0);
	assert(pos<frame->len_code);
	pos++;
	frame->pos_code=pos;
}

void INCR_INSTR2(JCONTEXT *context,size_t nb_inst)
{
	size_t pos;
	JFRAME *frame;
	assert(context!=NULL);
	assert(nb_inst>0);
	frame=context->frame;
	assert(frame!=NULL);
	pos=frame->pos_code;
	assert(pos>=0);
	assert(pos<frame->len_code);
	assert(pos+nb_inst<=frame->len_code);
	pos+=nb_inst;
	frame->pos_code=pos;
}

void affiche_opcode(uint8_t *buf,int len)
{
	int i,j;
	uint8_t c;
	char *nom=NULL;
	OPCODE_TABLE *opc,*trouve;

	printf("debut code\n");
	if(buf!=NULL)
	{
		for(i=0;i<len;i++)
		{
			c=buf[i];
			trouve=NULL;
			for(j=0;j<len_tab_opcode;j++)
			{
				opc=&table_opcode[j];
				if(opc->opcode==c)
				{
					trouve=opc;
					break;
				}
			}
			if(trouve!=NULL)
			{
				printf("%s(%X)",trouve->name,trouve->opcode);
				if(trouve->size_param>0)
				{
					i+=trouve->size_param;
					printf(" %d params",trouve->size_param);
				}
				printf("\n");
			}
			else
			{
				assert("opcode non trouve");
			}
		}
	}
	printf("fin code\n");
}

void remplit_opcode(JCONTEXT *context)
{
	uint8_t opcode;
	OPCODE_TABLE *opc,*trouve;
	uint8_t *buf=NULL,size_code;
	int i,j,pos;
	assert(context!=NULL);

	opcode=context->DONNE_INSTR_SUIVANTE(context);
	trouve=NULL;
	size_code=0;
	for(j=0;j<len_tab_opcode;j++)
	{
		opc=&table_opcode[j];
		if(opc->opcode==opcode)
		{
			trouve=opc;
			break;
		}
	}
	if(trouve!=NULL)
	{
		if(trouve->size_param>0)
		{
			buf=(uint8_t*)calloc(trouve->size_param,sizeof(uint8_t));
			pos=context->frame->pos_code;
			for(i=0;i<trouve->size_param;i++)
			{
				assert(pos+i+1>=0);
				assert(pos+i+1<context->frame->len_code);
				buf[i]=context->frame->code[pos+i+1];
			}
			size_code=trouve->size_param+1;
		}
		else
		{
			buf=NULL;
			size_code=1;
		}
	}
	else
	{
		opcode=0;
		buf=NULL;
		size_code=0;
	}
	context->opcode_courant=opcode;
	context->code_courant=buf;
	if(size_code>0)
	{
		INCR_INSTR2(context,size_code);
	}
}

void libere_opcode(JCONTEXT *context)
{
	assert(context!=NULL);

	context->opcode_courant=0;
	if(context->code_courant!=NULL)
	{
		free(context->code_courant);
		context->code_courant=NULL;
	}
}
