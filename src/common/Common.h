/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_COMMON_H
#define HTOPML_COMMON_H

/********************  HEADERS  *********************/
#include <cstdlib>
#include <sstream>
#include <string>

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
template <class T> std::string toString(const T & value)
{
	std::stringstream str;
	str << value;
	return str.str();
}

/*******************  FUNCTION  *********************/
char * loadFileInMemory(const std::string & fname,size_t * size = NULL,bool abortOnError = true);

};

#endif //HTOPML_COMMON_H
