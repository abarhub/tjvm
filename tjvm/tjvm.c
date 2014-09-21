// tjvm.cpp : définit le point d'entrée pour l'application console.
//

//#include "stdafx.h"

#include<stdio.h>
//#include <stdint.h>

#include "jclasse.h"
#include "parser.h"
#include "run.h"


//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
	char *fichier="..\\java\\Hello.class";//"C:\\Users\\Alain\\Documents\\Visual Studio 2010\\Projects\\tjvm\\java\\Hello.class";
	JCLASS* res;

	res=lecture(fichier);

	if(res!=NULL)
	{
		run2(res);
	}

	return 0;
}

