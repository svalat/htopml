/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_MENU_HTTP_NODE_H
#define HTOPML_MENU_HTTP_NODE_H

/********************  HEADERS  *********************/
#include "vector"
#include "JsonState.h"
#include "HttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  STRUCT  *********************/
struct MenuEntry
{
	std::string name;
	std::string url;
	std::string iconUrl;
};

/*********************  TYPES  **********************/
typedef std::vector<MenuEntry> MenuEntryVector;

/*********************  CLASS  **********************/
class MenuHttpNode : public HttpNode
{
	public:
		MenuHttpNode(const std::string& path,const std::string & listId);
		virtual void onHttpRequest(HttpResponse& response, const HttpRequest& request);
		void addEntry(const std::string & name,const std::string & url,const std::string & icon = "");
	private:
		std::string listId;
		MenuEntryVector entries;
};

/*******************  FUNCTION  *********************/
void convertToJson(JsonState & json, const MenuEntry & value);

}

#endif // HTOPML_VALIDATION_HTTP_NODE_H
