/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include <cstring>
#include "ValidationWebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
ValidationWebNode::ValidationWebNode(const std::string& path, bool strictPath)
	: WebNode(path, strictPath)
{

}

/*******************  FUNCTION  *********************/
WebNodeData ValidationWebNode::getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	char buffer[2048];
	sprintf(buffer,"Ok, get the page at URI : %s\n",request_info->uri);
	return WebNodeData(strdup(buffer),strlen(buffer),"text/plain",true);
}

}
