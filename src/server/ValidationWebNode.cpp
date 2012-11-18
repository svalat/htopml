/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
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
void ValidationWebNode::getContent(Response & response,const Request & request)
{
	response.setHttpStatus(200);
	response.printf("Ok, get the page at URI : %s\n",request.getUri().c_str());
}

}
