/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include "JsonObject.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
template <class T>
void JsonObject::registerField(const std::string& name, const T* field)
{
	fields.push_back(new JsonObjectFieldTyped<T>(name,field));
}

/*******************  FUNCTION  *********************/
template <class T>
void JsonObject::registerDeltaField(const std::string& name, const T* field)
{
	fields.push_back(new JsonObjectFieldDeltaTyped<T>(name,field));
}

/*******************  FUNCTION  *********************/
template <class T>
JsonObjectFieldTyped<T>::JsonObjectFieldTyped(const std::string& name, const T* value)
	:JsonObjectField(name,(void*)value)
{

}

/*******************  FUNCTION  *********************/
template <class T>
void JsonObjectFieldTyped<T>::typeToJson(JsonState& json, std::ostream& stream) const
{
	htopml::typeToJson(json,stream,*(const T*)value);
}

/*******************  FUNCTION  *********************/
template <class T>
JsonObjectFieldDeltaTyped<T>::JsonObjectFieldDeltaTyped(const std::string & name,const T * value)
	:JsonObjectField(name,(void*)value)
{
	this->init = false;
}

/*******************  FUNCTION  *********************/
template <class T>
void JsonObjectFieldDeltaTyped<T>::typeToJson(JsonState & json,std::ostream& stream) const
{
	if (this->init)
	{
		T delta = (*(const T*)value) - previous;
		htopml::typeToJson(json,stream,delta);
	} else {
		htopml::typeToJson(json,stream,*(const T*)value);
	}

	previous = *(const T*)value;
}

}
