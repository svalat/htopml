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
#include "../server/JsonWebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class GetRusageWebNode : public JsonWebNode<rusage>
{
	public:
		GetRusageWebNode(const std::string & addr);
		virtual void onRequest(const mg_request_info* request_info);
	private:
		rusage data;
};

/*******************  FUNCTION  *********************/
void typeToJson(JsonState & json,std::ostream& stream, const rusage & value);
void typeToJson(JsonState & json,std::ostream& stream, const timeval & value);

};

#endif // HTOPML_LINUX_GET_RUSAGE_WEB_NODE_H
