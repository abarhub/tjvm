#ifndef JERRORH
#define JERRORH

#include "jstr.h"

enum tjvm_Error_Type {ALLOC=1,CLASS_FORMAT=2};

typedef enum tjvm_Error_Type TJVM_ERROR_TYPE;

struct JError {
	int nb_error;
	JSTR **tab;
};

typedef struct JError JERROR;

JERROR *tjvm_create_error();

int tjvm_is_error(JERROR *err);
void tjvm_add_error(JERROR *err,JSTR * msg_error);
void tjvm_add_error_code(JERROR *err,TJVM_ERROR_TYPE code,JSTR * msg_error);
void tjvm_print_error(JERROR *err);

#endif