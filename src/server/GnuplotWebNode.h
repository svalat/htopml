/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef IHSTKGNUPLOTWEBNODE_H
#define IHSTKGNUPLOTWEBNODE_H

/********************  HEADERS  *********************/
#include "WebNode.h"

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*********************  CLASS  **********************/
class GnuplotWebNode : public WebNode
{
	public:
		GnuplotWebNode(const std::string& path, std::string command);
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info);
	private:
		std::string command;
};

};

#endif // IHSTKGNUPLOTWEBNODE_H
