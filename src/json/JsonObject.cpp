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
JsonObjectField::JsonObjectField(const std::string& name, const void* value)
{
	this->name = name;
	this->value = value;
}

/*******************  FUNCTION  *********************/
JsonObjectField::~JsonObjectField(void )
{
}

/*******************  FUNCTION  *********************/
const std::string& JsonObjectField::getName(void ) const
{
	return this->name;
}

/*******************  FUNCTION  *********************/
JsonObject::~JsonObject(void )
{
	for (JsonObjectFieldVector::iterator it = fields.begin() ; it != fields.end() ; ++it)
		delete *it;
}

/*******************  FUNCTION  *********************/
void JsonObject::typeToJson(JsonState& json, std::ostream& stream) const
{
	json.openStruct();
	for (JsonObjectFieldVector::const_iterator it = fields.begin() ; it != fields.end() ; ++it)
		json.printField((*it)->getName(),**it);
	json.closeStruct();
}

/*******************  FUNCTION  *********************/
void typeToJson(JsonState& json, std::ostream& stream, const JsonObject& object)
{
	object.typeToJson(json,stream);
}

/*******************  FUNCTION  *********************/
void typeToJson(JsonState& json, std::ostream& stream, const JsonObjectField& field)
{
	field.typeToJson(json,stream);
}

}
