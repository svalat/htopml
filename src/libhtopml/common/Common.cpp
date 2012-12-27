/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include "Common.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
/**
 * Function to quickly load a file in memory. It allocate a temporary buffer
 * which must be freed by the caller (with free()).
 * @param fname Define the file path to open.
 * @param size Pointer to size variable. If not NULL, will be updated with
 * the size of the loaded file.
 * @param abortOnError If true, abort on failure otherwise, return NULL and
 * -1 as size.
**/
char * loadFileInMemory(const std::string & fname,size_t * size,bool abortOnError)
{
	//vars
	char * buffer = NULL;
	FILE * fp;
	size_t tmp;

	//errors
	assert(!fname.empty());

	//open the file
	fp = fopen(fname.c_str(),"r");

	//check if OK
	if (fp == NULL)
	{
		cerr << "File not found : " << fname << endl;
		if (size != NULL)
			*size = -1;
		if (abortOnError)
			abort();
	} else {
		fseek(fp, 0L, SEEK_END);
		size_t fileSize = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		buffer = (char*)malloc(fileSize+1);
		buffer[fileSize] = '\0';
		if (size != NULL)
			*size = fileSize;
		tmp = fread(buffer,1,fileSize,fp);
		assert(tmp == fileSize);
		fclose(fp);
	}

	//return it
	return buffer;
}

}
