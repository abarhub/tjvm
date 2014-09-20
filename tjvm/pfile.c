#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "pfile.h"
#include "outils.h"


int file_valide(FILEBUFFER *f)
{
	assert(f!=NULL);
	assert(f->len>=0);
	assert(f->pos>=0);
	assert(f->pos<=f->len);
	assert((f->len==0&&f->buf==NULL)||(f->len>0&&f->buf!=NULL));
	return 1;
}

FILEBUFFER *readFile(char *filename)
{
	FILEBUFFER *res=NULL;
	int len=0;
	FILE *fp=NULL;
	size_t bytes_read=0;

	fp=fopen(filename, "rb");
	if(fp==NULL)
	{
		perror("Error in opening file");
		return NULL;
	}

	fseek(fp, 0L, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	
	if(len==0)
	{
		return NULL;
	}

	if( ferror(fp) )
    {
		perror("Error in reading file");
        printf("Error in reading from file : %s\n",filename);
		return NULL;
    }
	/*else if(feof(fp))
	{
		printf("End in reading from file : %s\n",filename);
		//return NULL;
	}* /
	else if(!feof(fp))
	{
		printf("Error in reading all from file : %s\n",filename);
		return NULL;
	}*/

	res=(FILEBUFFER*)calloc(1,sizeof(FILEBUFFER));

	res->buf=(char*)calloc(len+1,sizeof(char));
	res->pos=0;
	res->len=0;

	bytes_read = fread(res->buf, 1,len, fp);
	res->len=bytes_read;

	
	if( ferror(fp) )
    {
		perror("Error in reading file");
        printf("Error in reading from file : %s\n",filename);
		return NULL;
    }
	/*else if(!feof(fp))
	{
		printf("Error in reading all from file : %s\n",filename);
		return NULL;
	}*/

	fclose(fp);

	return res;
}

uint8_t read_uint8(FILEBUFFER *f)
{
	uint8_t val,tmp;
	unsigned int pos;
	char *p;
	uint8_t *buf;
	assert(f!=NULL);
	assert(file_len_dispo(f)>=1);
	//assert(f->pos+1<f->len);
	pos=f->pos;
	//buf=(uint8_t *)(f->buf+pos);
	//tmp=*buf[pos+1];
	//val=(*buf);
	val=*(f->buf+pos);
	//pshort=(unsigned short *)f->buf;
		//version_mineur=swap_uint16(*pshort);
		//pshort++;
	f->pos+=1;
	assert(file_valide(f));
	return val;
}

uint16_t read_uint16(FILEBUFFER *f)
{
	uint16_t val,tmp;
	unsigned int pos;
	char *p;
	uint16_t *buf;
	assert(f!=NULL);
	assert(file_len_dispo(f)>=2);
	//assert(f->pos+2<f->len);
	pos=f->pos;
	buf=(uint16_t *)(f->buf+pos);
	//tmp=*buf[pos+1];
	val=swap_uint16(*buf);
	//pshort=(unsigned short *)f->buf;
		//version_mineur=swap_uint16(*pshort);
		//pshort++;
	f->pos+=2;
	assert(file_valide(f));
	return val;
}

uint32_t read_uint32(FILEBUFFER *f)
{
	uint32_t val,tmp;
	unsigned int pos;
	char *p;
	uint32_t *buf;
	assert(f!=NULL);
	assert(file_len_dispo(f)>=4);
	//assert(f->pos+4<f->len);
	pos=f->pos;
	buf=(uint32_t *)(f->buf+pos);
	//tmp=*buf[pos+1];
	val=swap_uint32(*buf);
	//pshort=(unsigned short *)f->buf;
		//version_mineur=swap_uint16(*pshort);
		//pshort++;
	f->pos+=4;
	assert(file_valide(f));
	return val;
}

uint64_t read_uint64(FILEBUFFER *f)
{
	uint64_t val,tmp;
	unsigned int pos;
	char *p;
	uint64_t *buf;
	assert(f!=NULL);
	assert(file_len_dispo(f)>=8);
	//assert(f->pos+8<f->len);
	pos=f->pos;
	buf=(uint64_t *)(f->buf+pos);
	//tmp=*buf[pos+1];
	val=swap_uint64(*buf);
	//pshort=(unsigned short *)f->buf;
		//version_mineur=swap_uint16(*pshort);
		//pshort++;
	f->pos+=8;
	assert(file_valide(f));
	return val;
}


char *read_char(FILEBUFFER *f,int len)
{
	uint64_t val,tmp;
	unsigned int pos;
	char *p;
	char *buf,*buf2;
	assert(f!=NULL);
	assert(len>0);
	assert(file_len_dispo(f)>=len);
	//assert(f->pos+len<=f->len);
	pos=f->pos;
	buf=(f->buf+pos);
	buf2=(char*)calloc(len+1,1);
	strncpy(buf2,buf,len);
	buf2[len]=0;
	//tmp=*buf[pos+1];
	//val=swap_uint64(*buf);
	//pshort=(unsigned short *)f->buf;
		//version_mineur=swap_uint16(*pshort);
		//pshort++;
	f->pos+=len;
	assert(file_valide(f));
	return buf2;
}

uint64_t file_len_dispo(FILEBUFFER *f)
{
	uint64_t val;
	assert(f!=NULL);
	assert(file_valide(f));
	val=f->len-f->pos;
	if(val<0)
		val=0;
	return val;
}

