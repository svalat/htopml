/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef IHSTKVALIDATIONWEBNODE_H
#define IHSTKVALIDATIONWEBNODE_H

/********************  HEADERS  *********************/
#include "WebNode.h"

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*********************  CLASS  **********************/
class ValidationWebNode : public WebNode
{
	public:
		ValidationWebNode(const std::string& path, bool strictPath);
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info);
};

};

#endif // IHSTKVALIDATIONWEBNODE_H
