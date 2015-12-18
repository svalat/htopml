/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_PROCESS_WEB_NODE_H
#define HTOPML_PROCESS_WEB_NODE_H

/********************  HEADERS  *********************/
#include "HttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class ProcessHttpNode : public HttpNode
{
	public:
		ProcessHttpNode(const std::string& path, const std::string & mimetype = "");
		virtual void onHttpRequest(HttpResponse & response,const HttpRequest & request);
		virtual std::string genCommandOnRequest(const HttpRequest & request) = 0;
		virtual std::string genMimetypeOnEquest(const HttpRequest & request);
	private:
		std::string mimetype;
};

/*********************  CLASS  **********************/
class SimpleProcessHttpNode : public ProcessHttpNode
{
	public:
		SimpleProcessHttpNode(const std::string& path, const std::string & command,const std::string & mimetype = "");
		virtual std::string genCommandOnRequest(const HttpRequest & request);
	private:
		std::string command;
};

}

#endif // HTOPML_PROCESS_WEB_NODE_H
