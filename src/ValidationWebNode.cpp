/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#include <cstdio>
#include <cstring>
#include "ValidationWebNode.h"

namespace InternalHtmlSpyToolKit
{
ValidationWebNode::ValidationWebNode(const std::string& path, bool strictPath)
	: WebNode(path, strictPath)
{

}

WebNodeData ValidationWebNode::getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	char buffer[2048];
	sprintf(buffer,"Ok, get the page at URI : %s\n",request_info->uri);
	return WebNodeData(strdup(buffer),strlen(buffer),"text/plain");
}

}
