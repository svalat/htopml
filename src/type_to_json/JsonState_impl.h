/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef JSONSTATE_IMPL_H
#define JSONSTATE_IMPL_H

/********************  HEADERS  *********************/
#include "JsonState.h"

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*******************  FUNCTION  *********************/
template <class T>
void JsonState::printField(const char * name,const T & value)
{
	//print
	openField(name);
	typeToJson(*this,*out,value);
	closeField(name);
}

/*******************  FUNCTION  *********************/
template <class T>
void JsonState::printValue(const T & value)
{
	//check where we are
	assert(getState() & (JSON_STATE_FIELD | JSON_STATE_ARRAY | JSON_STATE_ROOT));

	//separator
	if (getState() == JSON_STATE_ARRAY && !isFirst())
		*out << ", ";

	//print
	typeToJson(*this,*out,value);

	firstIsDone();
}

/*******************  FUNCTION  *********************/
template <class T>
void JsonState::printFieldArray(const char * name,const T * value,int size)
{
	assert(value != NULL || size == 0);
	assert(size >= 0);

	//check where we are
	assert(getState() & (JSON_STATE_STRUCT | JSON_STATE_ROOT));

	openField(name);
	openArray();
	for (int i = 0 ; i < size ; i++)
		printValue(value[i]);
	closeArray();
	closeField(name);
}

/*******************  FUNCTION  *********************/
template <class T>
void JsonState::printArray(const T * value,int size)
{
	assert(value != NULL || size == 0);
	assert(size >= 0);

	//check where we are
	assert(getState() & (JSON_STATE_FIELD | JSON_STATE_ARRAY | JSON_STATE_ROOT));

	openArray();
	for (int i = 0 ; i < size ; i++)
		printValue(value[i]);
	closeArray();
}

};

#endif // JSONSTATE_IMPL_H
