#ifndef OPCODE2_H
#define OPCODE2_H

#include <stdint.h>
#include "context.h"

//enum ETYPE {TREF=1,TDOUBLE=2,TFLOAT=3,TINT=4,TLONG=5,TVOID=6,TBYTE=7};
//typedef enum ETYPE ETYPE;

//enum EOPERATEUR {TADD=1,TMULT=2,TSUB=3,TDIV=4,TAND=5,TOR=6,TXOR=7,TSHR=8,TSHL=9,TREM=10,TUSHR=11,};
//typedef enum EOPERATEUR EOPERATEUR;

void INSTR_LOAD(JCONTEXT *context,ETYPE type,int index_local,int param);
void INSTR_STORE(JCONTEXT *context,ETYPE type,int index_local,int param);
void INSTR_CONST(JCONTEXT *context,ETYPE type,int val,int param);
void INSTR_RETURN(JCONTEXT *context,ETYPE type);
void INSTR_OPBIN(JCONTEXT *context,ETYPE type,EOPERATEUR operateur);

void INSTR_DEBUT(JCONTEXT *context);
void INSTR_FIN(JCONTEXT *context);

void INSTR_ITERATION(JCONTEXT *context);

int EST_FINI(JCONTEXT *context);

uint8_t DONNE_INSTR_SUIVANTE(JCONTEXT *context);

void INCR_INSTR(JCONTEXT *context);

void INSTR_AUTRE(JCONTEXT *context);

void affiche_opcode(uint8_t *buf,int len);

void remplit_opcode(JCONTEXT *context);
void libere_opcode(JCONTEXT *context);

void INSTR_LDC(JCONTEXT *context,int type_op);

void affiche_frame(JFRAME *frame);

#endif
