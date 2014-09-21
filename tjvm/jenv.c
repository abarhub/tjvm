#include <assert.h>
#include <malloc.h>
#include <stdio.h>

#include "jenv.h"
#include "jerror.h"
#include "jstr.h"

JENV * tjvm_create_env()
{
	JENV *tmp;

	tmp=(JENV *)calloc(1,sizeof(JENV));

	if(tmp==NULL)
	{
		return NULL;
	}

	tmp->err=tjvm_create_error();

	if(tmp->err==NULL)
	{
		free(tmp);
		return NULL;
	}

	return tmp;
}


int tjvm_env_is_error(JENV *env)
{
	assert(env!=NULL);
	assert(env->err!=NULL);

	return tjvm_is_error(env->err);
}

void tjvm_env_add_error(JENV *env,JSTR *str)
{
	assert(env!=NULL);
	assert(env->err!=NULL);
	assert(str!=NULL);

	tjvm_add_error(env->err,str);
}

void tjvm_env_add_error_c(JENV *env,char *str)
{
	JSTR *s;
	assert(env!=NULL);
	assert(env->err!=NULL);
	assert(str!=NULL);

	s=createJStrC(str);

	tjvm_env_add_error(env,s);
}

void tjvm_env_add_log(JENV *env,JSTR *str)
{
	assert(env!=NULL);
	assert(env->err!=NULL);
}

void tjvm_env_add_log_c(JENV *env,char *str)
{
	assert(env!=NULL);
	assert(env->err!=NULL);
}