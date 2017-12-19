/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include "TypeToJson.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
/*void convertToJson(JsonState & json,std::ostream& stream, const std::string& value)
{
	return convertToJson(json,stream,value.c_str());
}*/

/*******************  FUNCTION  *********************/
/*void convertToJson(JsonState & json,std::ostream& stream, const char* value)
{
	stream << '\"';
	while (value != NULL && *value != '\0')
	{
		if (*value == '\"')
			stream << "\\\"";
		else
			stream << *value;
		value++;
	}
	stream << '"';
}*/

/*******************  FUNCTION  *********************/
/*void convertToJson(JsonState & json,std::ostream& stream, unsigned long value)
{
	stream << value;
}*/

/*******************  FUNCTION  *********************/
/*void convertToJson(JsonState & json,std::ostream& stream, long value)
{
	stream << value;
}*/

/*******************  FUNCTION  *********************/
/*void convertToJson(JsonState & json,std::ostream& stream, double value)
{
	stream << value;
}*/

/*void convertToJson(JsonState & json,std::ostream& stream, bool value)
{
	if (value)
		stream << "true";
	else
		stream << "false";
}*/

}
