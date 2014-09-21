
#include <malloc.h>
#include <stdio.h>
#include <assert.h>

#include "jerror.h"



JERROR *tjvm_create_error()
{
	JERROR *tmp;

	tmp=(JERROR *)calloc(1,sizeof(JERROR));

	tmp->nb_error=0;
	tmp->tab=NULL;

	return tmp;
}

int tjvm_is_error(JERROR *err)
{
	return err==NULL||err->nb_error>0;
}

void tjvm_add_error(JERROR *err,JSTR * msg_error)
{
	int nb_err;
	JSTR **tab;
	assert(err!=NULL);
	assert(msg_error!=NULL);

	nb_err=err->nb_error;
	
	if(nb_err==0)
	{
		tab=(JSTR**)calloc(1,sizeof(JSTR*));
		tab[0]=msg_error;
		nb_err++;
		err->tab=tab;
		err->nb_error=nb_err;
	}
	else
	{
		nb_err++;
		tab=(JSTR**)realloc(err->tab,nb_err*sizeof(JSTR*));
		tab[nb_err-1]=msg_error;
		err->tab=tab;
		err->nb_error=nb_err;
	}
}

void tjvm_add_error_code(JERROR *err,TJVM_ERROR_TYPE code,JSTR * msg_error)
{
	tjvm_add_error(err,msg_error);
}

void tjvm_print_error(JERROR *err)
{
	int i=0;

	for(i=0;i<err->nb_error;i++)
	{
		jstrprintnl(err->tab[i]);
	}
}
