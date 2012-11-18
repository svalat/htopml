/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_LINUX_GET_RUSAGE_WEB_NODE_H
#define HTOPML_LINUX_GET_RUSAGE_WEB_NODE_H

/********************  HEADERS  *********************/
#include <sys/time.h>
#include <sys/resource.h>
#include "../server/JsonHttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class GetRusageHttpNode : public JsonHttpNode<rusage>
{
	public:
		GetRusageHttpNode(const std::string & addr);
		virtual void onRequest(const HttpRequest & request);
	private:
		rusage data;
};

/*******************  FUNCTION  *********************/
void typeToJson(JsonState & json,std::ostream& stream, const rusage & value);
void typeToJson(JsonState & json,std::ostream& stream, const timeval & value);

};

#endif // HTOPML_LINUX_GET_RUSAGE_WEB_NODE_H
