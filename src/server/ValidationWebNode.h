/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_VALIDATION_WEB_NODE_H
#define HTOPML_VALIDATION_WEB_NODE_H

/********************  HEADERS  *********************/
#include "WebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class ValidationWebNode : public WebNode
{
	public:
		ValidationWebNode(const std::string& path, bool strictPath);
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info);
};

};

#endif // HTOPML_VALIDATION_WEB_NODE_H
