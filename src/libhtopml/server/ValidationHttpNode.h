/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_VALIDATION_HTTP_NODE_H
#define HTOPML_VALIDATION_HTTP_NODE_H

/********************  HEADERS  *********************/
#include "HttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class ValidationHttpNode : public HttpNode
{
	public:
		ValidationHttpNode(const std::string& path, bool strictPath);
	virtual void onHttpRequest(HttpResponse& response, const HttpRequest& request);
};

}

#endif // HTOPML_VALIDATION_HTTP_NODE_H
