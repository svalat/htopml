/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_IN_APP_H
#define HTOPML_IN_APP_H

/********************  HEADERS  *********************/
#ifdef __cplusplus
	#include "HtopmlHttpServer.h"
#endif //__cplusplus

/********************  GLOBALS  *********************/
extern int gblHtopmlIsEnabled;

/********************  MACRO  ***********************/
/**
 * Equivalent to HTOPML_ACTION() for those who prefer to write their own 
 * if/else.
**/
#ifdef HAVE_HTOPML
	#define HTOPML_IS_ENABLED() gblHtopmlIsEnabled
#else //HAVE_HTOPML
	#define HTOPML_IS_ENABLED() 0
#endif //HAVE_HTOPML

/********************  MACRO  ***********************/
/**
 * Macro to wrap htopml actions in application. By this way we can quickly
 * enable or disable them at build time with HAVE_HTOPML or at runtime
 * with inert htopml version.
**/
#ifdef HAVE_HTOPML
	#define HTOPML_ACTION(x) do{if(HTOPML_IS_ENABLED()) {x;}} while(0)
#else //HAVE_HTOPML
	#define HTOPML_ACTION(x) do{} while(0)
#endif //HAVE_HTOPML

/*******************  FUNCTION  *********************/
#ifdef HAVE_HTOPML
	#define HTOPML_UPDATE_GENERIC_VALUE(name,value) HTOPML_ACTION(htopml_update_generic_value((name),(value)))
#else //HAVE_HTOPML
	#define HTOPML_UPDATE_GENERIC_VALUE(name,value) do{} while(0)
#endif

/*******************  FUNCTION  *********************/
#ifdef __cplusplus
extern "C" {
#endif
void htopml_update_generic_value(const char * name,double value);
#ifdef __cplusplus
}
#endif
	
#endif //HTOPML_IN_APP_H
