/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_JSON_WEB_NODE_H
#define HTOPML_JSON_WEB_NODE_H

/********************  HEADERS  *********************/
#include <sstream>
#include <cstring>
#include "WebNode.h"
#include "../json/TypeToJson.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
template <class T>
class JsonWebNode : public WebNode
{
	public:
		JsonWebNode(const std::string& path, const T * value);
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info);
	protected:
		virtual void onRequest(const mg_request_info* request_info);
	private:
		const T * value;
};

/*******************  FUNCTION  *********************/
template <class T>
JsonWebNode<T>::JsonWebNode(const std::string& path, const T* value)
	: WebNode(path, true)
{
	this->value = value;
}

/*******************  FUNCTION  *********************/
template <class T>
WebNodeData JsonWebNode<T>::getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	std::stringstream str;
	onRequest(request_info);
	typeToJson(str,*value);
	char * res = strdup(str.str().c_str());
	return WebNodeData(res,strlen(res),"application/json",200,true);
}

/*******************  FUNCTION  *********************/
template <class T>
void JsonWebNode<T>::onRequest(const mg_request_info* request_info)
{
	
}

};

#endif // HTOPML_JSON_WEB_NODE_H
