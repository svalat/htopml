/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
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
		virtual void getContent(Response & response,const Request & request);
};

};

#endif // HTOPML_VALIDATION_WEB_NODE_H
