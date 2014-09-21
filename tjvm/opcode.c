// généré le Sun Sep 21 17:17:51 CEST 2014

#include <stdio.h>
#include <assert.h>
#include "opcode.h"
#include "context.h"
#include "opcode2.h"

OPCODE_TABLE table_opcode[]={
{AALOAD,"aaload",0}
,{AASTORE,"aastore",0}
,{ACONST_NULL,"aconst_null",0}
,{ALOAD,"aload",1}
,{ALOAD_0,"aload_0",0}
,{ALOAD_1,"aload_1",0}
,{ALOAD_2,"aload_2",0}
,{ALOAD_3,"aload_3",0}
,{ANEWARRAY,"anewarray",2}
,{ARETURN,"areturn",0}
,{ARRAYLENGTH,"arraylength",0}
,{ASTORE,"astore",1}
,{ASTORE_0,"astore_0",0}
,{ASTORE_1,"astore_1",0}
,{ASTORE_2,"astore_2",0}
,{ASTORE_3,"astore_3",0}
,{ATHROW,"athrow",0}
,{BALOAD,"baload",0}
,{BASTORE,"bastore",0}
,{BIPUSH,"bipush",1}
,{BREAKPOINT,"breakpoint",0}
,{CALOAD,"caload",0}
,{CASTORE,"castore",0}
,{CHECKCAST,"checkcast",2}
,{D2F,"d2f",0}
,{D2I,"d2i",0}
,{D2L,"d2l",0}
,{DADD,"dadd",0}
,{DALOAD,"daload",0}
,{DASTORE,"dastore",0}
,{DCMPG,"dcmpg",0}
,{DCMPL,"dcmpl",0}
,{DCONST_0,"dconst_0",0}
,{DCONST_1,"dconst_1",0}
,{DDIV,"ddiv",0}
,{DLOAD,"dload",1}
,{DLOAD_0,"dload_0",0}
,{DLOAD_1,"dload_1",0}
,{DLOAD_2,"dload_2",0}
,{DLOAD_3,"dload_3",0}
,{DMUL,"dmul",0}
,{DNEG,"dneg",0}
,{DREM,"drem",0}
,{DRETURN,"dreturn",0}
,{DSTORE,"dstore",1}
,{DSTORE_0,"dstore_0",0}
,{DSTORE_1,"dstore_1",0}
,{DSTORE_2,"dstore_2",0}
,{DSTORE_3,"dstore_3",0}
,{DSUB,"dsub",0}
,{DUP,"dup",0}
,{DUP_X1,"dup_x1",0}
,{DUP_X2,"dup_x2",0}
,{DUP2,"dup2",0}
,{DUP2_X1,"dup2_x1",0}
,{DUP2_X2,"dup2_x2",0}
,{F2D,"f2d",0}
,{F2I,"f2i",0}
,{F2L,"f2l",0}
,{FADD,"fadd",0}
,{FALOAD,"faload",0}
,{FASTORE,"fastore",0}
,{FCMPG,"fcmpg",0}
,{FCMPL,"fcmpl",0}
,{FCONST_0,"fconst_0",0}
,{FCONST_1,"fconst_1",0}
,{FCONST_2,"fconst_2",0}
,{FDIV,"fdiv",0}
,{FLOAD,"fload",1}
,{FLOAD_0,"fload_0",0}
,{FLOAD_1,"fload_1",0}
,{FLOAD_2,"fload_2",0}
,{FLOAD_3,"fload_3",0}
,{FMUL,"fmul",0}
,{FNEG,"fneg",0}
,{FREM,"frem",0}
,{FRETURN,"freturn",0}
,{FSTORE,"fstore",1}
,{FSTORE_0,"fstore_0",0}
,{FSTORE_1,"fstore_1",0}
,{FSTORE_2,"fstore_2",0}
,{FSTORE_3,"fstore_3",0}
,{FSUB,"fsub",0}
,{GETFIELD,"getfield",2}
,{GETSTATIC,"getstatic",2}
,{GOTO,"goto",2}
,{GOTO_W,"goto_w",4}
,{I2B,"i2b",0}
,{I2C,"i2c",0}
,{I2D,"i2d",0}
,{I2F,"i2f",0}
,{I2L,"i2l",0}
,{I2S,"i2s",0}
,{IADD,"iadd",0}
,{IALOAD,"iaload",0}
,{IAND,"iand",0}
,{IASTORE,"iastore",0}
,{ICONST_M1,"iconst_m1",0}
,{ICONST_0,"iconst_0",0}
,{ICONST_1,"iconst_1",0}
,{ICONST_2,"iconst_2",0}
,{ICONST_3,"iconst_3",0}
,{ICONST_4,"iconst_4",0}
,{ICONST_5,"iconst_5",0}
,{IDIV,"idiv",0}
,{IF_ACMPEQ,"if_acmpeq",2}
,{IF_ACMPNE,"if_acmpne",2}
,{IF_ICMPEQ,"if_icmpeq",2}
,{IF_ICMPGE,"if_icmpge",2}
,{IF_ICMPGT,"if_icmpgt",2}
,{IF_ICMPLE,"if_icmple",2}
,{IF_ICMPLT,"if_icmplt",2}
,{IF_ICMPNE,"if_icmpne",2}
,{IFEQ,"ifeq",2}
,{IFGE,"ifge",2}
,{IFGT,"ifgt",2}
,{IFLE,"ifle",2}
,{IFLT,"iflt",2}
,{IFNE,"ifne",2}
,{IFNONNULL,"ifnonnull",2}
,{IFNULL,"ifnull",2}
,{IINC,"iinc",2}
,{ILOAD,"iload",1}
,{ILOAD_0,"iload_0",0}
,{ILOAD_1,"iload_1",0}
,{ILOAD_2,"iload_2",0}
,{ILOAD_3,"iload_3",0}
,{IMPDEP1,"impdep1",0}
,{IMPDEP2,"impdep2",0}
,{IMUL,"imul",0}
,{INEG,"ineg",0}
,{INSTANCEOF,"instanceof",2}
,{INVOKEDYNAMIC,"invokedynamic",4}
,{INVOKEINTERFACE,"invokeinterface",4}
,{INVOKESPECIAL,"invokespecial",2}
,{INVOKESTATIC,"invokestatic",2}
,{INVOKEVIRTUAL,"invokevirtual",2}
,{IOR,"ior",0}
,{IREM,"irem",0}
,{IRETURN,"ireturn",0}
,{ISHL,"ishl",0}
,{ISHR,"ishr",0}
,{ISTORE,"istore",1}
,{ISTORE_0,"istore_0",0}
,{ISTORE_1,"istore_1",0}
,{ISTORE_2,"istore_2",0}
,{ISTORE_3,"istore_3",0}
,{ISUB,"isub",0}
,{IUSHR,"iushr",0}
,{IXOR,"ixor",0}
,{JSR,"jsr",2}
,{JSR_W,"jsr_w",4}
,{L2D,"l2d",0}
,{L2F,"l2f",0}
,{L2I,"l2i",0}
,{LADD,"ladd",0}
,{LALOAD,"laload",0}
,{LAND,"land",0}
,{LASTORE,"lastore",0}
,{LCMP,"lcmp",0}
,{LCONST_0,"lconst_0",0}
,{LCONST_1,"lconst_1",0}
,{LDC,"ldc",1}
,{LDC_W,"ldc_w",2}
,{LDC2_W,"ldc2_w",2}
,{LDIV,"ldiv",0}
,{LLOAD,"lload",1}
,{LLOAD_0,"lload_0",0}
,{LLOAD_1,"lload_1",0}
,{LLOAD_2,"lload_2",0}
,{LLOAD_3,"lload_3",0}
,{LMUL,"lmul",0}
,{LNEG,"lneg",0}
,{LOOKUPSWITCH,"lookupswitch",0}
,{LOR,"lor",0}
,{LREM,"lrem",0}
,{LRETURN,"lreturn",0}
,{LSHL,"lshl",0}
,{LSHR,"lshr",0}
,{LSTORE,"lstore",1}
,{LSTORE_0,"lstore_0",0}
,{LSTORE_1,"lstore_1",0}
,{LSTORE_2,"lstore_2",0}
,{LSTORE_3,"lstore_3",0}
,{LSUB,"lsub",0}
,{LUSHR,"lushr",0}
,{LXOR,"lxor",0}
,{MONITORENTER,"monitorenter",0}
,{MONITOREXIT,"monitorexit",0}
,{MULTIANEWARRAY,"multianewarray",3}
,{NEW,"new",2}
,{NEWARRAY,"newarray",1}
,{NOP,"nop",0}
,{POP,"pop",0}
,{POP2,"pop2",0}
,{PUTFIELD,"putfield",2}
,{PUTSTATIC,"putstatic",2}
,{RET,"ret",1}
,{RETURN,"return",0}
,{SALOAD,"saload",0}
,{SASTORE,"sastore",0}
,{SIPUSH,"sipush",2}
,{SWAP,"swap",0}
,{TABLESWITCH,"tableswitch",0}
,{WIDE,"wide",0}
};
int len_tab_opcode=205;

void execute(JCONTEXT *context) {
	assert(context!=NULL);
	context->INSTR_DEBUT(context);
	while(!context->EST_FINI(context)) {
		context->INSTR_ITERATION(context);
		remplit_opcode(context);
		switch(context->opcode_courant){
			case ACONST_NULL: context->INSTR_CONST(context,TREF,0,0);break;
			case ALOAD: context->INSTR_LOAD(context,TREF,0,1);break;
			case ALOAD_0: context->INSTR_LOAD(context,TREF,0,0);break;
			case ALOAD_1: context->INSTR_LOAD(context,TREF,1,0);break;
			case ALOAD_2: context->INSTR_LOAD(context,TREF,2,0);break;
			case ALOAD_3: context->INSTR_LOAD(context,TREF,3,0);break;
			case ASTORE: context->INSTR_STORE(context,TREF,0,1);break;
			case ASTORE_0: context->INSTR_STORE(context,TREF,0,0);break;
			case ASTORE_1: context->INSTR_STORE(context,TREF,1,0);break;
			case ASTORE_2: context->INSTR_STORE(context,TREF,2,0);break;
			case ASTORE_3: context->INSTR_STORE(context,TREF,3,0);break;
			case BIPUSH: context->INSTR_CONST(context,TBYTE,0,1);break;
			case DCONST_0: context->INSTR_CONST(context,TDOUBLE,0,0);break;
			case DCONST_1: context->INSTR_CONST(context,TDOUBLE,1,0);break;
			case DLOAD: context->INSTR_LOAD(context,TDOUBLE,0,1);break;
			case DLOAD_0: context->INSTR_LOAD(context,TDOUBLE,0,0);break;
			case DLOAD_1: context->INSTR_LOAD(context,TDOUBLE,1,0);break;
			case DLOAD_2: context->INSTR_LOAD(context,TDOUBLE,2,0);break;
			case DLOAD_3: context->INSTR_LOAD(context,TDOUBLE,3,0);break;
			case DSTORE: context->INSTR_STORE(context,TDOUBLE,0,1);break;
			case DSTORE_0: context->INSTR_STORE(context,TDOUBLE,0,0);break;
			case DSTORE_1: context->INSTR_STORE(context,TDOUBLE,1,0);break;
			case DSTORE_2: context->INSTR_STORE(context,TDOUBLE,2,0);break;
			case DSTORE_3: context->INSTR_STORE(context,TDOUBLE,3,0);break;
			case FCONST_0: context->INSTR_CONST(context,TFLOAT,0,0);break;
			case FCONST_1: context->INSTR_CONST(context,TFLOAT,1,0);break;
			case FCONST_2: context->INSTR_CONST(context,TFLOAT,2,0);break;
			case FLOAD: context->INSTR_LOAD(context,TFLOAT,0,1);break;
			case FLOAD_0: context->INSTR_LOAD(context,TFLOAT,0,0);break;
			case FLOAD_1: context->INSTR_LOAD(context,TFLOAT,1,0);break;
			case FLOAD_2: context->INSTR_LOAD(context,TFLOAT,2,0);break;
			case FLOAD_3: context->INSTR_LOAD(context,TFLOAT,3,0);break;
			case FSTORE: context->INSTR_STORE(context,TFLOAT,0,1);break;
			case FSTORE_0: context->INSTR_STORE(context,TFLOAT,0,0);break;
			case FSTORE_1: context->INSTR_STORE(context,TFLOAT,1,0);break;
			case FSTORE_2: context->INSTR_STORE(context,TFLOAT,2,0);break;
			case FSTORE_3: context->INSTR_STORE(context,TFLOAT,3,0);break;
			case IADD: context->INSTR_OPBIN(context,TINT,TADD);break;
			case IAND: context->INSTR_OPBIN(context,TINT,TAND);break;
			case ICONST_M1: context->INSTR_CONST(context,TINT,-1,0);break;
			case ICONST_0: context->INSTR_CONST(context,TINT,0,0);break;
			case ICONST_1: context->INSTR_CONST(context,TINT,1,0);break;
			case ICONST_2: context->INSTR_CONST(context,TINT,2,0);break;
			case ICONST_3: context->INSTR_CONST(context,TINT,3,0);break;
			case ICONST_4: context->INSTR_CONST(context,TINT,4,0);break;
			case ICONST_5: context->INSTR_CONST(context,TINT,5,0);break;
			case IDIV: context->INSTR_OPBIN(context,TINT,TDIV);break;
			case ILOAD: context->INSTR_LOAD(context,TINT,0,1);break;
			case ILOAD_0: context->INSTR_LOAD(context,TINT,0,0);break;
			case ILOAD_1: context->INSTR_LOAD(context,TINT,1,0);break;
			case ILOAD_2: context->INSTR_LOAD(context,TINT,2,0);break;
			case ILOAD_3: context->INSTR_LOAD(context,TINT,3,0);break;
			case IMUL: context->INSTR_OPBIN(context,TINT,TMULT);break;
			case IOR: context->INSTR_OPBIN(context,TINT,TOR);break;
			case IREM: context->INSTR_OPBIN(context,TINT,TREM);break;
			case ISHL: context->INSTR_OPBIN(context,TINT,TSHL);break;
			case ISHR: context->INSTR_OPBIN(context,TINT,TSHR);break;
			case ISTORE: context->INSTR_STORE(context,TINT,0,1);break;
			case ISTORE_0: context->INSTR_STORE(context,TINT,0,0);break;
			case ISTORE_1: context->INSTR_STORE(context,TINT,1,0);break;
			case ISTORE_2: context->INSTR_STORE(context,TINT,2,0);break;
			case ISTORE_3: context->INSTR_STORE(context,TINT,3,0);break;
			case ISUB: context->INSTR_OPBIN(context,TINT,TSUB);break;
			case IUSHR: context->INSTR_OPBIN(context,TINT,TUSHR);break;
			case IXOR: context->INSTR_OPBIN(context,TINT,TXOR);break;
			case LADD: context->INSTR_OPBIN(context,TLONG,TADD);break;
			case LAND: context->INSTR_OPBIN(context,TLONG,TAND);break;
			case LCONST_0: context->INSTR_CONST(context,TLONG,0,0);break;
			case LCONST_1: context->INSTR_CONST(context,TLONG,1,0);break;
			case LDC: context->INSTR_LDC(context,0);break;
			case LDC_W: context->INSTR_LDC(context,1);break;
			case LDC2_W: context->INSTR_LDC(context,2);break;
			case LDIV: context->INSTR_OPBIN(context,TLONG,TDIV);break;
			case LLOAD: context->INSTR_LOAD(context,TLONG,0,1);break;
			case LLOAD_0: context->INSTR_LOAD(context,TLONG,0,0);break;
			case LLOAD_1: context->INSTR_LOAD(context,TLONG,1,0);break;
			case LLOAD_2: context->INSTR_LOAD(context,TLONG,2,0);break;
			case LLOAD_3: context->INSTR_LOAD(context,TLONG,3,0);break;
			case LMUL: context->INSTR_OPBIN(context,TLONG,TMULT);break;
			case LOR: context->INSTR_OPBIN(context,TLONG,TOR);break;
			case LREM: context->INSTR_OPBIN(context,TLONG,TREM);break;
			case LSHL: context->INSTR_OPBIN(context,TLONG,TSHL);break;
			case LSHR: context->INSTR_OPBIN(context,TLONG,TSHR);break;
			case LSTORE: context->INSTR_STORE(context,TLONG,0,1);break;
			case LSTORE_0: context->INSTR_STORE(context,TLONG,0,0);break;
			case LSTORE_1: context->INSTR_STORE(context,TLONG,1,0);break;
			case LSTORE_2: context->INSTR_STORE(context,TLONG,2,0);break;
			case LSTORE_3: context->INSTR_STORE(context,TLONG,3,0);break;
			case LSUB: context->INSTR_OPBIN(context,TLONG,TSUB);break;
			case LUSHR: context->INSTR_OPBIN(context,TLONG,TUSHR);break;
			case LXOR: context->INSTR_OPBIN(context,TLONG,TXOR);break;
			case RETURN: context->INSTR_RETURN(context,TVOID);break;
			default: context->INSTR_AUTRE(context);break;
		}
	}
	context->INSTR_FIN(context);
}
