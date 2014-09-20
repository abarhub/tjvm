#ifndef PFILEH
#define PFILEH

//#include <stdint.h>

struct fileBuffer {
	unsigned int len;
	char *buf;
	unsigned int pos;
};

typedef struct fileBuffer FILEBUFFER;

FILEBUFFER *readFile(char *filename);
uint16_t read_uint16(FILEBUFFER *f);
uint32_t read_uint32(FILEBUFFER *f);
uint64_t read_uint64(FILEBUFFER *f);
char *read_char(FILEBUFFER *f,int len);
uint8_t read_uint8(FILEBUFFER *f);
uint64_t file_len_dispo(FILEBUFFER *f);

#endif