/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include <cstring>
#include "ValidationHttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
ValidationHttpNode::ValidationHttpNode(const std::string& path, bool strictPath)
	: HttpNode(path, strictPath)
{

}

/*******************  FUNCTION  *********************/
void ValidationHttpNode::onHttpRequest(HttpResponse& response, const HttpRequest& request)
{
	response.setHttpStatus(200);
	response.printf("Ok, get the page at URI : %s\n",request.getUri().c_str());
}

}
