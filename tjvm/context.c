#include<malloc.h>
#include<stdio.h>
#include<assert.h>

#include "context.h"
#include "opcode2.h"

JCONTEXT *new_context_run(JCLASS *classe,JMETHOD_INFO *methode)
{
	JCONTEXT * tmp=NULL;

	assert(classe!=NULL);
	assert(methode!=NULL);
	tmp=(JCONTEXT*)calloc(1,sizeof(JCONTEXT));
	tmp->classe=classe;
	tmp->methode=methode;

	tmp->INSTR_LOAD=&INSTR_LOAD;
	tmp->INSTR_STORE=&INSTR_STORE;
	tmp->INSTR_CONST=&INSTR_CONST;
	tmp->INSTR_RETURN=&INSTR_RETURN;
	tmp->INSTR_OPBIN=&INSTR_OPBIN;
	tmp->INSTR_DEBUT=&INSTR_DEBUT;
	tmp->INSTR_FIN=&INSTR_FIN;
	tmp->INSTR_ITERATION=&INSTR_ITERATION;
	tmp->INCR_INSTR=&INCR_INSTR;
	tmp->INSTR_AUTRE=&INSTR_AUTRE;
	tmp->EST_FINI=&EST_FINI;
	tmp->DONNE_INSTR_SUIVANTE=&DONNE_INSTR_SUIVANTE;

	tmp->code_courant=NULL;
	tmp->opcode_courant=0;

	return tmp;
}


