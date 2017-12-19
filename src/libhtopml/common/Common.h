/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
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
/**
 * Quick function wrapper to convert a generic value to string format
 * if stream operators are supported. It return it as a C++ string.
 * @param value Define the value to convert.
**/
template <class T> std::string toString(const T & value)
{
	std::stringstream str;
	str << value;
	return str.str();
}

/*******************  FUNCTION  *********************/
char * loadFileInMemory(const std::string & fname,size_t * size = NULL,bool abortOnError = true);

}

#endif //HTOPML_COMMON_H
