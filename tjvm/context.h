#ifndef CONTEXT_H
#define CONTEXT_H

#include "jclasse.h"


struct JFrame {
	unsigned int nb_var_local;
	uint32_t *var_local;
	unsigned int nb_stack;
	uint32_t *stack;
	unsigned int pos_stack;
	unsigned int pos_code;
	JCLASS *classe;
	CODE_ATTRIBUTE *methode;
	//JMETHOD_INFO *methode_attr;
	unsigned int len_code;
	uint8_t *code;
	struct JFrame *precedent;
};

typedef struct JFrame JFRAME;

enum ETYPE {TREF=1,TDOUBLE=2,TFLOAT=3,TINT=4,TLONG=5,TVOID=6,TBYTE=7};
typedef enum ETYPE ETYPE;

enum EOPERATEUR {TADD=1,TMULT=2,TSUB=3,TDIV=4,TAND=5,TOR=6,TXOR=7,TSHR=8,TSHL=9,TREM=10,TUSHR=11,};
typedef enum EOPERATEUR EOPERATEUR;

struct jContext {
	JCLASS *classe;
	JMETHOD_INFO *methode;
	//uint8_t *code_bin;
	//size_t len_code_bin;
	//size_t pos_code;
	JFRAME *frame;
	int fini;
	uint8_t opcode_courant;
	uint8_t *code_courant;

	// les methodes
	void (*INSTR_LOAD)(struct jContext *context,ETYPE type,int index_local,int param);
	//void (*toto)(int a,int b);
	void (*INSTR_STORE)(struct jContext *context,ETYPE type,int index_local,int param);
	void (*INSTR_CONST)(struct jContext *context,ETYPE type,int val,int param);
	void (*INSTR_RETURN)(struct jContext *context,ETYPE type);
	void (*INSTR_OPBIN)(struct jContext *context,ETYPE type,EOPERATEUR operateur);

	void (*INSTR_DEBUT)(struct jContext *context);
	void (*INSTR_FIN)(struct jContext *context);

	void (*INSTR_ITERATION)(struct jContext *context);

	void (*INCR_INSTR)(struct jContext *context);

	void (*INSTR_AUTRE)(struct jContext *context);

	int (*EST_FINI)(struct jContext *context);
	uint8_t (*DONNE_INSTR_SUIVANTE)(struct jContext *context);
};
typedef struct jContext JCONTEXT;

JCONTEXT *new_context_run(JCLASS *classe,JMETHOD_INFO *methode);

#endif