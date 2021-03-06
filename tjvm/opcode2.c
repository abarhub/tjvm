#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <malloc.h>

#include "opcode.h"
#include "opcode2.h"

void affiche_opcode(uint8_t *buf,int len);

static void push_stack_val_int(JFRAME *frame,int32_t val)
{
	TYPEVALSTACK *p;
	assert(frame!=NULL);
	assert(frame->pos_stack>=0);
	assert(frame->pos_stack<frame->nb_stack);

	p=&(frame->stack_val[frame->pos_stack]);
	assert(p->type_val==EInt32Stack||p->type_val==0);
	p->val_int=val;
	p->type_val=EInt32Stack;
	frame->pos_stack++;
}

static int32_t pop_stack_int(JFRAME *frame)
{
	int32_t val;
	TYPEVALSTACK *p;
	assert(frame!=NULL);
	assert(frame->pos_stack>0);
	p=&(frame->stack_val[frame->pos_stack-1]);
	assert(p->type_val==EInt32Stack);
	val=p->val_int;
	frame->pos_stack--;
	return val;
}

static void set_var_local_int(JFRAME *frame,uint16_t no_var,uint32_t val)
{
	TYPEVALSTACK *p;
	assert(frame!=NULL);
	assert(frame->nb_var_local>0);
	assert(no_var>=0);
	assert(no_var<frame->nb_var_local);
	//frame->var_local[no_var]=val;
	p=&(frame->local_val[no_var]);
	assert(p->type_val==EInt32Stack||p->type_val==0);
	p->type_val=EInt32Stack;
	p->val_int=val;
}

static uint32_t get_var_local_int(JFRAME *frame,uint16_t no_var)
{
	uint32_t val;
	assert(frame!=NULL);
	assert(frame->nb_var_local>=0);
	assert(no_var>=0);
	assert(no_var<frame->nb_var_local);
	assert(frame->local_val[no_var].type_val==EInt32Stack);
	val=frame->local_val[no_var].val_int;
	return val;
}

static void push_stack_val_float(JFRAME *frame,float val)
{
	TYPEVALSTACK *p;
	assert(frame!=NULL);
	assert(frame->pos_stack>=0);
	assert(frame->pos_stack<frame->nb_stack);
	//frame->stack[frame->pos_stack]=val;
	p=&(frame->stack_val[frame->pos_stack]);
	p->type_val=EFloatStack;
	p->val_float=val;
	frame->pos_stack++;
}

static float pop_stack_float(JFRAME *frame)
{
	float val;
	TYPEVALSTACK *p;
	assert(frame!=NULL);
	assert(frame->pos_stack>0);
	p=&(frame->stack_val[frame->pos_stack-1]);
	assert(p->type_val==EFloatStack);
	val=p->val_float;
	frame->pos_stack--;
	return val;
}

static void set_var_local_float(JFRAME *frame,uint16_t no_var,float val)
{
	TYPEVALSTACK *p;
	assert(frame!=NULL);
	assert(frame->nb_var_local>0);
	assert(no_var>=0);
	assert(no_var<frame->nb_var_local);
	p=&(frame->local_val[no_var]);
	assert(p->type_val==EFloatStack||p->type_val==0);
	//frame->var_local[no_var]=val;
	p->type_val=EFloatStack;
	p->val_float=val;
}

static float get_var_local_float(JFRAME *frame,uint16_t no_var)
{
	float val;
	TYPEVALSTACK *p;
	assert(frame!=NULL);
	assert(frame->nb_var_local>=0);
	assert(no_var>=0);
	assert(no_var<frame->nb_var_local);
	p=&(frame->local_val[no_var]);
	assert(p->type_val==EFloatStack);
	val=p->val_float;
	return val;
}

void affiche_frame(JFRAME *frame)
{
	if(frame==NULL)
	{
		printf("Frame vide\n");
	}
	else
	{
		int nb_var_max,nb_stack_max,pos_stack,pos_code;
		int i;
		TYPEVALSTACK *p;
		nb_var_max=frame->nb_var_local;
		nb_stack_max=frame->nb_stack;
		pos_stack=frame->pos_stack;
		pos_code=frame->pos_code;
		printf("var:");
		for(i=0;i<nb_var_max;i++)
		{
			p=&(frame->local_val[i]);
			if(p->type_val==EInt32Stack)
			{
				printf("%d ",p->val_int);
			}
			else if(p->type_val==EFloatStack)
			{
				printf("%f ",p->val_float);
			}
			else if(p->type_val==EDoubleStack1)
			{
				printf("%lf ",p->val_double);
			}
			else if(p->type_val==ELongStack1)
			{
				printf("%ld ",p->val_long);
			}
			else if(p->type_val==ERefStack)
			{
				printf("%x ",p->ref);
			}
			else
			{
				printf("X ");
			}
		}
		printf("\n");
		printf("stack (%d):",pos_stack);
		for(i=0;i<nb_stack_max;i++)
		{
			//printf("%d ",frame->stack[i]);
			p=&(frame->stack_val[i]);
			if(p->type_val==EInt32Stack)
			{
				printf("%d ",p->val_int);
			}
			else if(p->type_val==EFloatStack)
			{
				printf("%f ",p->val_float);
			}
			else if(p->type_val==EDoubleStack1)
			{
				printf("%lf ",p->val_double);
			}
			else if(p->type_val==ELongStack1)
			{
				printf("%ld ",p->val_long);
			}
			else if(p->type_val==ERefStack)
			{
				printf("%x ",p->ref);
			}
			else
			{
				printf("X ");
			}
		}
		printf("\n");
	}
}

void INSTR_LOAD(JCONTEXT *context,ETYPE type,int index_local,int param)
{
	assert(context!=NULL);

	if(type==TINT)
	{// le type int
		if(param==0)
		{
			uint16_t no_var;
			uint32_t val=0;
			no_var=index_local;
			assert(no_var>=0&&no_var<=3);
			val=get_var_local_int(context->frame,no_var);
			push_stack_val_int(context->frame,val);
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
			val=get_var_local_int(context->frame,no_var);
			push_stack_val_int(context->frame,val);
			//INCR_INSTR(context);
		}
	}
	else if(type==TFLOAT)
	{// le type float
		if(param==0)
		{
			uint16_t no_var;
			float val=0;
			no_var=index_local;
			assert(no_var>=0&&no_var<=3);
			val=get_var_local_float(context->frame,no_var);
			push_stack_val_float(context->frame,val);
		}
		else
		{
			uint8_t no;
			uint16_t no_var;
			float val=0;
			no_var=context->code_courant[0];
			assert(no_var>=0);
			val=get_var_local_float(context->frame,no_var);
			push_stack_val_float(context->frame,val);
		}
	}
	else
	{
		assert(1==0);
	}

	
}

void INSTR_STORE(JCONTEXT *context,ETYPE type,int index_local,int param)
{
	uint16_t no_var;
	assert(context!=NULL);
	
	if(type==TINT)
	{// type int
		int32_t val;
		val=pop_stack_int(context->frame);
		if(param==0)
		{
			no_var=index_local;
			assert(no_var>=0&&no_var<=3);
			set_var_local_int(context->frame,no_var,val);
			//INCR_INSTR(context);
		}
		else
		{
			//INCR_INSTR(context);
			//no_var=DONNE_INSTR_SUIVANTE(context);
			no_var=context->code_courant[0];
			assert(no_var>=0);
			set_var_local_int(context->frame,no_var,val);
			//INCR_INSTR(context);
		}
	}
	else if(type==TFLOAT)
	{// type float
		float val;
		val=pop_stack_float(context->frame);
		if(param==0)
		{
			no_var=index_local;
			assert(no_var>=0&&no_var<=3);
			set_var_local_float(context->frame,no_var,val);
		}
		else
		{
			no_var=context->code_courant[0];
			assert(no_var>=0);
			set_var_local_float(context->frame,no_var,val);
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

	assert(context!=NULL);

	if(type==TINT)
	{
		int32_t val0=0;
		if(param==0)
		{
			val0=val;
			assert(val0>=-1&&val0<=5);
			push_stack_val_int(context->frame,val0);
			//INCR_INSTR(context);
		}
		else
		{
			//INCR_INSTR(context);
			//val0=DONNE_INSTR_SUIVANTE(context);
			val0=context->code_courant[0];
			push_stack_val_int(context->frame,val0);
			//INCR_INSTR(context);
		}
	}
	else if(type==TBYTE)
	{
		int32_t val0=0;
		if(param==1)
		{
			//INCR_INSTR(context);
			//val0=DONNE_INSTR_SUIVANTE(context);
			val0=context->code_courant[0];
			push_stack_val_int(context->frame,val0);
			//INCR_INSTR(context);
		}
		else
		{
			assert(1==0);
		}
	}
	else if(type==TFLOAT)
	{
		float val0=0.0;
		if(param==0)
		{
			assert(val>=0&&val<=2);
			val0=val;
			push_stack_val_float(context->frame,val0);
			//INCR_INSTR(context);
		}
		else
		{
			//INCR_INSTR(context);
			//val0=DONNE_INSTR_SUIVANTE(context);
			val0=context->code_courant[0];
			push_stack_val_float(context->frame,val0);
			//INCR_INSTR(context);
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
		val=pop_stack_int(context->frame);
		val2=pop_stack_int(context->frame);
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
		push_stack_val_int(context->frame,val);
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

void INSTR_LDC(JCONTEXT *context,int type_op)
{
	assert(context!=NULL);

	if(type_op==0||type_op==1)
	{
		uint8_t tag;
		int pos=0;
		unsigned int index1=0,index2=0;
		CP_INFO * cp;

		index1=context->code_courant[0];
		assert(index1>=0);
		assert(index1<context->classe->constant_pool_count);
		if(type_op==0)
		{
			pos=index1;
		}
		else if(type_op==1)
		{
			index2=context->code_courant[1];
			assert(index2>=0);
			pos=(index1<<8)+index2;
		}
		else
		{
			assert(1==0);
		}
		assert(pos>0);
		assert(pos<=context->classe->constant_pool_count);
		cp=&(context->classe->constant_pool[pos-1]);
		tag=cp->tag;
		if(tag==CONSTANT_Float)
		{
			float f;
			f=cp->val_float;
			push_stack_val_float(context->frame,f);
		}
		else if(tag==CONSTANT_Integer)
		{
			int i;
			i=cp->val_int;
			push_stack_val_int(context->frame,i);
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
	//printf("Fin\n");
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
