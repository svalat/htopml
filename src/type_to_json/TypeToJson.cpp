/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include "TypeToJson.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*******************  FUNCTION  *********************/
ostream& typeToJsonPadding(ostream& out, int padding)
{
	for (int i = 0 ; i < padding ; i++)
		out << '\t';
	return out;
}

/*******************  FUNCTION  *********************/
ostream& typeToJsonVarName(ostream& out, int padding, const string& name)
{
	if (name.empty() == false)
	{
		typeToJsonPadding(out,padding);
		out << name << ": ";
		return out;
	}
	return out;
}

/*******************  FUNCTION  *********************/
ostream& typeToJson(std::ostream& out,int padding, const std::string & name, const std::string& value)
{
	return typeToJson(out,padding,name,value.c_str());
}

/*******************  FUNCTION  *********************/
ostream& typeToJson(ostream& out, int padding, const string& name, const char* value)
{
	//name
	typeToJsonVarName(out,padding,name);

	out << '\"';
	while (value != NULL && *value != '\0')
	{
		if (*value == '\"')
			out << "\\\"";
		else
			out << *value;
		value++;
	}
	out << "\"," << endl;
	return out;
}

/*******************  FUNCTION  *********************/
ostream& typeToJson(ostream& out, int padding, const string& name, unsigned long value)
{
	//name
	typeToJsonVarName(out,padding,name);
	out << value;
	out << "\"," << endl;
	return out;
}

/*******************  FUNCTION  *********************/
ostream& typeToJson(ostream& out, int padding, const string& name, long value)
{
	//name
	typeToJsonVarName(out,padding,name);
	out << value;
	out << "\"," << endl;
	return out;
}

/*******************  FUNCTION  *********************/
ostream& typeToJson(ostream& out, int padding, const string& name, double value)
{
	//name
	typeToJsonVarName(out,padding,name);
	out << value;
	out << "\"," << endl;
	return out;
}

/*******************  FUNCTION  *********************/
template <class T> std::ostream& typeToJson(std::ostream& out,int padding, const T & value)
{
	return typeToJson(out,padding,"",value);
}

};
