/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_TYPE_TO_JSON_H
#define HTOPML_TYPE_TO_JSON_H

/********************  HEADERS  *********************/
#include <ostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "JsonState.h"
#include "ConvertToJson.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/********************  MACRO  ***********************/
#define IHSTK_TYPE_TO_JSON_BASIC_TYPE(alias_type,target_type) \
	static inline void convertToJson(JsonState & json,alias_type value) {return convertToJson(json,(target_type)value);}

/*******************  FUNCTION  *********************/
//template <class T> std::ostream& convertToJson(std::ostream& out,const T & value);
//template <class T> std::ostream& convertToJson(std::ostream& out,const T * value);

/*******************  FUNCTION  *********************/
//void convertToJson(JsonState & json,std::ostream& stream, const std::string& value);
//void convertToJson(JsonState & json,std::ostream& stream, const char * value);
//void convertToJson(JsonState & json,std::ostream& stream, long value);
//void convertToJson(JsonState & json,std::ostream& stream, unsigned long value);
//void convertToJson(JsonState & json,std::ostream& stream, double value);
//void convertToJson(JsonState & json,std::ostream& stream, bool value);

/*******************  FUNCTION  *********************/
//template <class T> void convertToJson(JsonState & json,std::ostream& stream, const std::vector<T> & iterable);
//template <class T> void convertToJson(JsonState & json,std::ostream& stream, const std::list<T> & iterable);
//template <class T,class U> void convertToJson(JsonState & json,std::ostream& stream, const std::map<T,U> & iterable);

/*******************  FUNCTION  *********************/
//IHSTK_TYPE_TO_JSON_BASIC_TYPE(int,long)
//IHSTK_TYPE_TO_JSON_BASIC_TYPE(unsigned int,unsigned long)
//IHSTK_TYPE_TO_JSON_BASIC_TYPE(float,double)

}

#include "TypeToJson_impl.h"

#endif //HTOPML_TYPE_TO_JSON_H
