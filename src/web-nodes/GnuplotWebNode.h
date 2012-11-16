/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_GNUPLOT_WEB_NODE_H
#define HTOPML_GNUPLOT_WEB_NODE_H

/********************  HEADERS  *********************/
#include "../server/WebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class GnuplotWebNode : public WebNode
{
	public:
		GnuplotWebNode(const std::string& path, const std::string & command);
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info);
	private:
		std::string command;
};

};

#endif // HTOPML_GNUPLOT_WEB_NODE_H
