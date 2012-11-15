/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdarg>
#include <cassert>
#include <cstdio>
#include "JsonState.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*******************  FUNCTION  *********************/
JsonState::JsonState(std::ostream* out)
{
	this->out = out;
	this->indent = 0;
	this->stateStack.push(JSON_STATE_ROOT);
}

/*******************  FUNCTION  *********************/
void JsonState::putPadding()
{
	for (int i = 0 ; i < indent ; i++)
		*out << '\t';
}

/*******************  FUNCTION  *********************/
JsonStateEnum JsonState::getState(void ) const
{
	return stateStack.top();
}

/*******************  FUNCTION  *********************/
void JsonState::printFormattedField(const char * name, const char* format, ... )
{
	char buffer[1024];

	//format the chain
	va_list param;
	va_start (param, format);
	vsnprintf (buffer,sizeof(buffer), format, param);
	va_end (param);

	//print
	openField(name);
	*out << buffer;
	closeField(name);
}

/*******************  FUNCTION  *********************/
void JsonState::printFormattedValue(const char* format, ... )
{
	char buffer[1024];

	//check where we are
	assert(getState() & (JSON_STATE_FIELD | JSON_STATE_ARRAY));

	//print
	*out << buffer;

	//separator
	if (getState() == JSON_STATE_ARRAY)
		*out << ", ";
}

/*******************  FUNCTION  *********************/
void JsonState::openField(const string& name)
{
	//check where we are
	assert(getState() & (JSON_STATE_ROOT | JSON_STATE_STRUCT));

	//setup state
	stateStack.push(JSON_STATE_FIELD);

	//print padding
	putPadding();

	//print name
	*out << name << ": ";
}

/*******************  FUNCTION  *********************/
void JsonState::closeField(const string& name)
{
	//check where we are
	assert(getState() == JSON_STATE_FIELD);

	//setup state
	stateStack.pop();

	//print name
	*out << ";" << endl;
}

/*******************  FUNCTION  *********************/
void JsonState::openArray(void)
{
	//check where we are
	assert(getState() & (JSON_STATE_ROOT | JSON_STATE_FIELD));

	//setup state
	stateStack.push(JSON_STATE_ARRAY);

	//print name
	*out << "[ ";
}

/*******************  FUNCTION  *********************/
void JsonState::closeArray(void)
{
	//check where we are
	assert(getState() == JSON_STATE_ARRAY);

	//setup state
	stateStack.pop();

	//print name
	*out << "]";
}

/*******************  FUNCTION  *********************/
void JsonState::openStruct(void )
{
		//check where we are
	assert(getState() & (JSON_STATE_FIELD | JSON_STATE_ARRAY | JSON_STATE_ROOT));

	//setup state
	stateStack.push(JSON_STATE_STRUCT);

	//print name
	indent++;
	*out << "{" << endl;
}

/*******************  FUNCTION  *********************/
void JsonState::closeStruct(void )
{
	//check where we are
	assert(getState() == JSON_STATE_STRUCT);

	//setup state
	stateStack.pop();

	//print name
	indent--;
	putPadding();
	*out << "}";
}

};
