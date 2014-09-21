// tjvm.cpp : définit le point d'entrée pour l'application console.
//

//#include "stdafx.h"

#include<stdio.h>
//#include <stdint.h>

#include "jclasse.h"
#include "parser.h"
#include "run.h"
#include "jerror.h"
#include "jenv.h"


//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
	char *fichier="..\\java\\Hello.class";//"C:\\Users\\Alain\\Documents\\Visual Studio 2010\\Projects\\tjvm\\java\\Hello.class";
	JCLASS* res;
	//JERROR *err;
	JENV *env;

	//err=tjvm_create_error();
	env=tjvm_create_env();

	res=lecture(fichier,env);

	if(tjvm_env_is_error(env))
	{
		jstrprintnl(createJStrC("Erreur du parsing :"));
		tjvm_print_error(env->err);
	}
	else
	{
		if(res!=NULL)
		{
			run2(res,env);
		}
	}

	return 0;
}

