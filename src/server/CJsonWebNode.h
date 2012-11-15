/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef IHSTKCJSONWEBNODE_H
#define IHSTKCJSONWEBNODE_H

/********************  HEADERS  *********************/
#include <sstream>
#include <cstring>
#include "WebNode.h"
#include "../type_to_json/TypeToJson.h"

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*********************  CLASS  **********************/
template <class T>
class CJsonWebNode : public WebNode
{
	public:
		CJsonWebNode(const std::string& path, const T * value);
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info);
	private:
		const T * value;
};

/*******************  FUNCTION  *********************/
template <class T>
CJsonWebNode<T>::CJsonWebNode(const std::string& path, const T* value)
	: WebNode(path, true)
{
	this->value = value;
}

/*******************  FUNCTION  *********************/
template <class T>
WebNodeData CJsonWebNode<T>::getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	std::stringstream str;
	typeToJson(str,*value);
	char * res = strdup(str.str().c_str());
	return WebNodeData(res,strlen(res),"application/json",200,true);
}

};

#endif // IHSTKCJSONWEBNODE_H
