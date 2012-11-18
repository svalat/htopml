/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_JSON_DELTAO_BJECT_H
#define HTOPML_JSON_DELTAO_BJECT_H

/********************  HEADERS  *********************/
#include <string>
#include <vector>
#include "JsonState.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class JsonObjectField
{
	public:
		JsonObjectField(const std::string & name,const void * value);
		virtual ~JsonObjectField(void);
		virtual void typeToJson(JsonState & json,std::ostream& stream) const = 0;
		const std::string & getName(void) const;
	protected:
		std::string name;
		const void * value;
};

/*********************  CLASS  **********************/
template <class T>
class JsonObjectFieldTyped : public JsonObjectField
{
	public:
		JsonObjectFieldTyped(const std::string & name,const T * value);
		virtual void typeToJson(JsonState & json,std::ostream& stream) const;
};

/*********************  CLASS  **********************/
template <class T>
class JsonObjectFieldDeltaTyped : public JsonObjectField
{
	public:
		JsonObjectFieldDeltaTyped(const std::string & name,const T * value);
		virtual void typeToJson(JsonState & json,std::ostream& stream) const;
	private:
		bool init;
		T previous;
};

/*********************  TYPES  **********************/
typedef std::vector<JsonObjectField*> JsonObjectFieldVector;

/*********************  CLASS  **********************/
class JsonObject
{
	public:
		virtual ~JsonObject(void);
		virtual void typeToJson(JsonState & json,std::ostream& stream) const;
	protected:
		template <class T> void registerField(const std::string & name,const T * field);
		template <class T> void registerDeltaField(const std::string & name,const T * field);
	private:
		JsonObjectFieldVector fields;
};

/*******************  FUNCTION  *********************/
void typeToJson(JsonState & json,std::ostream& stream, const JsonObject & object);
void typeToJson(JsonState & json,std::ostream& stream, const JsonObjectField & field);

};

#include "JsonObject_impl.h"

#endif // HTOPML_JSON_DELTAO_BJECT_H
