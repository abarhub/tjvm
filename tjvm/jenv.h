#ifndef JENVH
#define JENVH

#include "jerror.h"
#include "jstr.h"

struct JEnv {
	JERROR *err;
};

typedef struct JEnv JENV;

JENV * tjvm_create_env();

int tjvm_env_is_error(JENV *env);

void tjvm_env_add_error(JENV *env,JSTR *str);
void tjvm_env_add_error_c(JENV *env,char *str);

void tjvm_env_add_log(JENV *env,JSTR *str);
void tjvm_env_add_log_c(JENV *env,char *str);

#endif