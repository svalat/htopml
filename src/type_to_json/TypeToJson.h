/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef TYPE_TO_JSON_H
#define TYPE_TO_JSON_H

/********************  HEADERS  *********************/
#include <ostream>
#include <string>
#include <vector>
#include <list>

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/********************  MACRO  ***********************/
#define IHSTK_TYPE_TO_JSON_BASIC_TYPE(alias_type,target_type) \
	static inline std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, alias_type value) {return typeToJson(out,padding,name,(target_type)value);}

/*******************  FUNCTION  *********************/
std::ostream & typeToJsonPadding(std::ostream & out,int padding);
std::ostream & typeToJsonVarName(std::ostream & out,int padding,const std::string & name);

/*******************  FUNCTION  *********************/
template <class T> std::ostream& typeToJson(std::ostream& out,const T & value);

/*******************  FUNCTION  *********************/
std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, const std::string& value);
std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, const char * value);
std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, long value);
std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, unsigned long value);
std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, double value);

/*******************  FUNCTION  *********************/
template <class T> std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, const std::vector<T> & iterable);
template <class T> std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, const std::list<T> & iterable);
template <class T> std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, const T * array,size_t size);

/*******************  FUNCTION  *********************/
IHSTK_TYPE_TO_JSON_BASIC_TYPE(int,long);
IHSTK_TYPE_TO_JSON_BASIC_TYPE(unsigned int,unsigned long);
IHSTK_TYPE_TO_JSON_BASIC_TYPE(float,double);

};

#include "TypeToJson_impl.h"

#endif //TYPE_TO_JSON_H
