#ifndef JSTRH
#define JSTRH

enum EEncodage {EUTF8=1,EUTF16BE=2,EUTF16LE=3,EUTF32=4,EUTF8J=5};

struct jstr {
	enum EEncodage encodage;
	unsigned int len;
	char *buf;
};

typedef struct jstr JSTR;

JSTR* createJStr(char *buf,int len,enum EEncodage encodage_src);

JSTR* createJStrC(char *buf);

void jstrprint(JSTR *str);

int jstrEquals(JSTR *s,JSTR *s2);

#endif