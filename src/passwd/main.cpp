/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <pwd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include "mongoose.h"

/**********************  USING  *********************/
using namespace std;

/*******************  FUNCTION  *********************/
int main(int argc, char **argv)
{
	//vars
	string home = getenv("HOME");
	string file = home + "/.htopmlpass";
	int res1,res2;

	if (argc == 2)
	{
		char * pass = getpass("Password : ");
		res1 = mg_modify_passwords_file(file.c_str(),"htopml",argv[1],pass);
		res2 = chmod(file.c_str(),S_IWUSR|S_IRUSR);
		return res1 + res2;
	} else if (argc == 3) {
		res1 = mg_modify_passwords_file(file.c_str(),"htopml",argv[1],argv[2]);
		res2 = chmod(file.c_str(),S_IWUSR|S_IRUSR);
		return res1 + res2;
	} else {
		fprintf(stderr,"Invalid arguments. Usage : %s {user} [password]\nIt will setup or edit %s.\n",argv[0],file.c_str());
		return EXIT_FAILURE;
	}
}
