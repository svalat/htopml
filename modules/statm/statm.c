/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "statm.h"

/*********************  CONSTS  *********************/
static const char * CST_STATM_FILE = "/proc/self/statm";

/*******************  FUNCTION  *********************/
void statm_load(struct statm* stat)
{
	int cnt;
	FILE * fp = fopen(CST_STATM_FILE,"r");
	if (fp == NULL)
	{
		perror(CST_STATM_FILE);
		abort();
	}

	cnt = fscanf(fp,"%lu %lu %lu %lu %lu %lu %lu\n",
	       &stat->size,&stat->resident, &stat->share, &stat->text, &stat->lib, &stat->data, &stat->dirty);
	assert(cnt == 7);

	fclose(fp);
}
