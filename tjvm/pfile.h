#ifndef PFILEH
#define PFILEH

//#include <stdint.h>

#include "jerror.h"
#include "jenv.h"

struct fileBuffer {
	unsigned int len;
	char *buf;
	unsigned int pos;
};

typedef struct fileBuffer FILEBUFFER;

FILEBUFFER *readFile(char *filename,JENV *env);
uint16_t read_uint16(FILEBUFFER *f,JENV *env);
uint32_t read_uint32(FILEBUFFER *f,JENV *env);
uint64_t read_uint64(FILEBUFFER *f,JENV *env);
char *read_char(FILEBUFFER *f,int len,JENV *env);
uint8_t read_uint8(FILEBUFFER *f,JENV *env);
uint64_t file_len_dispo(FILEBUFFER *f);

#endif