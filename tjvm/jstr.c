#include <stdint.h>
#include "jstr.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/*
détermination de la taille du codage du caractere
*/
static int len_char(char c)
{
	int len=0;
	if((c&0x80)==0)
	{// 0xxx
		len=1;
	}
	else 
	{// 1xxxx
		if((c&0xC0)==1)
		{// 11xxxx
			if((c&0xE0)==1)
			{// 111xxxx
				if((c&0xF0)==1)
				{// 1111xxxx
					len=4;
				}
				else
				{// 1110xxxx
					len=3;
				}
			}
			else
			{// 10xxxx
				len=2;
			}
		}
		else
		{// 10xxxx
			assert(1==0);
		}
	}
	
	return len;
}

size_t len_utf8_to_utf16(char *buf,size_t len)
{
	size_t len2,len3;
	int i,j,pos;
	unsigned short code_unicode;
	unsigned char c,c2,c3,c4;
	unsigned short *p;

	len2=0;
	for(i=0;i<len;i++)
	{
		c=buf[i];
		len3=len_char(c);
		assert(len3>0);
		if(len3==1||len3==2||len3==3)
		{
			len2+=2;
		}
		else if(len3==4)
		{
			len2+=4;
		}
	}
	return len2;
}

JSTR* createJStr(char *buf,size_t len,enum EEncodage encodage_src)
{
	JSTR *tmp;
	char *tmp2;
	int len2,len3;

	tmp=(JSTR*)calloc(1,sizeof(JSTR));
	tmp->encodage=EUTF16LE;

	if((encodage_src==EUTF8)||(encodage_src==EUTF8J))
	{
		int i,j,pos;
		unsigned short code_unicode;
		unsigned char c,c2,c3,c4;
		unsigned short *p;
		len2=len_utf8_to_utf16(buf,len);
		/*len2=0;
		for(i=0;i<len;i++)
		{
			c=buf[i];
			len3=len_char(c);
			assert(len3>0);
			if(len3==1||len3==2||len3==3)
			{
				len2+=2;
			}
			else if(len3==4)
			{
				len2+=4;
			}
		}*/
		tmp2=(char*)calloc(len2+1,sizeof(char));
		//strncpy(tmp2,buf,len2);
		pos=0;
		for(i=0;i<len;i++)
		{
			c=buf[i];
			len3=len_char(c);
			assert(len3>0);
			if(len3==1)
			{
				code_unicode=c;
				assert(code_unicode<=0x7F);
				p=(unsigned short *)(tmp2+pos);
				*p=code_unicode;
				pos+=2;
			}
			else if(len3==2)
			{
				c2=buf[i+1];

				c &= ~((1 << 8)+(1 << 7));
				c2 &= ~(1 << 8);
				code_unicode=(c<<7)+c2;
				
				assert(code_unicode>0x7F);

				p=(unsigned short *)(tmp2+pos);
				*p=code_unicode;
				pos+=2;
			}
			else if(len3==3)
			{
				c2=buf[i+1];
				c3=buf[i+2];

				c &= ~((1 << 8)+(1 << 7)+(1 << 6));
				c2 &= ~(1 << 8);
				c3 &= ~(1 << 8);
				code_unicode=(c<<13)+(c2<<7)+c3;

				p=(unsigned short *)(tmp2+pos);
				*p=code_unicode;
				pos+=2;
			}
			else if(len3==4)
			{
				uint32_t code;
				c2=buf[i+1];
				c3=buf[i+2];
				c4=buf[i+3];

				c &= ~((1 << 8)+(1 << 7)+(1 << 6)+(1 << 5));
				c2 &= ~(1 << 8);
				c3 &= ~(1 << 8);
				c4 &= ~(1 << 8);
				code=(c<<3)+(c2>>4);
				code--;
				code=(code<<5)+((c2<<4)>>4);
				code=(code<<7)+c3;
				code=(code<<7)+c4;
				code_unicode=(1 << 16)+(1 << 15)+(1 << 13)+(1 << 12)+(code>>10);

				p=(unsigned short *)(tmp2+pos);
				*p=code_unicode;
				pos+=2;

				code_unicode=(1 << 16)+(1 << 15)+(1 << 13)+(1 << 12)+(1 << 11)+((code<<6)>>6);
				p=(unsigned short *)(tmp2+pos);
				*p=code_unicode;
				pos+=2;
			}
			else
			{
				assert(1==0);
			}
		}
		tmp->len=len2;
		tmp->buf=tmp2;
	}
	/*else if(encodage_src==EUTF8J)
	{
		len2=len;
		tmp2=(char*)calloc(len2+1,sizeof(char));
		strncpy(tmp2,buf,len2);
		tmp->len=len2;
		tmp->buf=tmp2;
	}*/
	else
	{
		assert(1==0);
	}

	/*tmp->buf=(char*)calloc(len+1,sizeof(char));
	strncpy(tmp->buf,buf,len);
	tmp->len=len;*/

	return tmp;
}

JSTR* createJStrC(char *buf)
{
	assert(buf!=NULL);
	return createJStr(buf,strlen(buf),EUTF8);
}

void jstrprint(JSTR *str)
{
	int i;
	wchar_t c;

	assert(str!=NULL);

	//printf("%s",str->buf);
	//wprintf((wchar_t*)str->buf);
	for(i=0;i<str->len;i+=2)
	{
		c=*((uint16_t*)(str->buf+i));
		putwchar(c);
	}
}

void jstrprintnl(JSTR *str)
{
	JSTR *nl;
	assert(str!=NULL);

	jstrprint(str);

	nl=createJStrC("\n");

	jstrprint(nl);

	jstrFree(nl);
}

void jstrFree(JSTR *s)
{
	assert(s!=NULL);
	
	if(s->buf!=NULL)
	{
		free(s->buf);
		s->buf=NULL;
	}
	free(s);
}

/*
retourne 1 ssi s==s2
*/
int jstrEquals(JSTR *s,JSTR *s2)
{
	int i;
	if(s==NULL&&s2==NULL)
	{// ils sont tous les 2 nulles
		return 1;
	}
	if(s==NULL||s2==NULL)
	{// un seul est null
		return 0;
	}
	if(s->len!=s2->len)
	{// ils n'ont pas la même taille
		return 0;
	}
	if(s->encodage!=s2->encodage)
	{// l'encodage et différent (non géré)
		return 0;
	}
	for(i=0;i<s->len;i++)
	{
		if(s->buf[i]!=s2->buf[i])
		{// le caractère n'est pas le même
			return 0;
		}
	}
	return 1;
}

void jstrAddC(char *s)
{

}

