/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef JSONSTATE_H
#define JSONSTATE_H

/********************  HEADERS  *********************/
#include <ostream>
#include <stack>
#include <cassert>

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

enum JsonStateEnum
{
	JSON_STATE_ROOT   = 1,
	JSON_STATE_STRUCT = 2,
	JSON_STATE_ARRAY  = 4,
	JSON_STATE_FIELD  = 8,
};

/*********************  TYPES  **********************/
struct JsonStateStruct
{
	JsonStateEnum state;
	bool isFirst;
};

/*********************  TYPES  **********************/
typedef std::stack<JsonStateStruct> JsonStateStructStack;

/*********************  CLASS  **********************/
class JsonState
{
	public:
		JsonState(std::ostream * out);
		template <class T> void printField(const char * name,const T & value);
		template <class T> void printValue(const T & value);
		template <class T> void printFieldArray(const char * name,const T * value,int size);
		template <class T> void printArray(const T * value,int size);
		void printFormattedField(const char * name,const char * format,...);
		void printFormattedValue(const char * format,...);
		void openArray(void);
		void closeArray(void);
		void openStruct(void);
		void closeStruct(void);
		JsonStateEnum getState(void) const;
	private:
		JsonState(const JsonState & state);;
		void openField(const std::string & name);
		void closeField(const std::string & name);
		void pushState(JsonStateEnum state);
		void popState(JsonStateEnum state);
		bool isFirst(void) const;
		void firstIsDone(void);
	private:
		void putPadding();
		std::ostream * out;
		int indent;
		JsonStateStructStack stateStack;
};

};

#include "JsonState_impl.h"

#endif // JSONSTATE_H
