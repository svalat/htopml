/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef TYPE_TO_JSON_IMPL_H
#define TYPE_TO_JSON_IMPL_H

/********************  HEADERS  *********************/
#include "TypeToJson.h"

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*******************  FUNCTION  *********************/
template <class T> std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, const std::vector<T> & iterable)
{
	typeToJsonVarName(out,padding,name);
	out << "[" << std::endl;

	for (typename std::vector<T>::iterator it = iterable.begin() ; it != iterable.end() ; ++it)
		typeToJson(out,padding+1,"",iterable);

	typeToJsonPadding(out,padding);
	out << "]," << std::endl;
	return out;
}

/*******************  FUNCTION  *********************/
template <class T> std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, const std::list<T> & iterable)
{
	typeToJsonVarName(out,padding,name);
	out << "[" << std::endl;

	for (typename std::vector<T>::iterator it = iterable.begin() ; it != iterable.end() ; ++it)
		typeToJson(out,padding+1,"",iterable);

	typeToJsonPadding(out,padding);
	out << "]," << std::endl;
	return out;
}

/*******************  FUNCTION  *********************/
template <class T> std::ostream& typeToJson(std::ostream& out,int padding, const std::string & name, const T * array,size_t size)
{
	typeToJsonVarName(out,padding,name);
	out << "[" << std::endl;

	if (array != NULL)
		for (int i = 0 ; i < size ; i++)
			typeToJson(out,padding+1,"",array[i]);

	typeToJsonPadding(out,padding);
	out << "]," << std::endl;
	return out;
}

};

#endif //TYPE_TO_JSON_H
