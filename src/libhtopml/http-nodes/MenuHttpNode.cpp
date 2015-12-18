/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include "TypeToJson.h"
#include "MenuHttpNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CONSTS  *********************/
static const char CST_JS_TEMPLATE[]="\n\
$(document).ready(function() {\n\
	var list = document.getElementById(\"%s\");\n\
	\n\
	list.innerHTML = \"%s\";\n\
};\n";

/*******************  FUNCTION  *********************/
MenuHttpNode::MenuHttpNode(const std::string& path,const std::string & listId)
	: HttpNode(path,true),listId(listId)
{
	
}

/*******************  FUNCTION  *********************/
void MenuHttpNode::onHttpRequest(HttpResponse& response, const HttpRequest& request)
{
	//set mime type
	response.setMimeType("application/javascript");

	//get quick access to stream
	std::ostream & out = response.getStream();

	//generate output
	out << "var " << listId << " = " << endl;
	convertToJson(out,entries);
	out << ";" << endl;
}

/*******************  FUNCTION  *********************/
void MenuHttpNode::addEntry(const std::string& name, const std::string& url, const std::string& icon)
{
	MenuEntry entry = {name,url,icon};
	this->entries.push_back(entry);
}

/*******************  FUNCTION  *********************/
void convertToJson(JsonState& json, const MenuEntry& value)
{
	json.openStruct();
	json.printField("name",value.name);
	json.printField("url",value.url);
	json.printField("iconUrl",value.iconUrl);
	json.closeStruct();
}

}
