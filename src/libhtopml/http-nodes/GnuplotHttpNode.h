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
#include "ProcessHttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class GnuplotHttpNode : public ProcessHttpNode
{
	public:
		GnuplotHttpNode(const std::string& path, const std::string & command);
		virtual std::string genCommandOnRequest(const HttpRequest& request);
	private:
		std::string command;
};

}

#endif // HTOPML_GNUPLOT_WEB_NODE_H