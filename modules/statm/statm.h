/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_LINUX_PROC_STATM_H
#define HTOPML_LINUX_PROC_STATM_H

/********************  HEADERS  *********************/

#ifdef __cplusplus
extern "C"
{
#endif

/*********************  STRUCT  *********************/
struct statm
{
	size_t size;
	size_t resident;
	size_t share;
	size_t text;
	size_t lib;
	size_t data;
	size_t dirty;
	
};

/*******************  FUNCTION  *********************/
void statm_load(struct statm * stat);

#ifdef __cplusplus
};
#endif

#endif
