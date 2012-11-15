/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef LINUXGETRUSAGEJSONWEBNODE_H
#define LINUXGETRUSAGEJSONWEBNODE_H

/********************  HEADERS  *********************/
#include <sys/time.h>
#include <sys/resource.h>
#include "../server/CJsonWebNode.h"

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*********************  CLASS  **********************/
class LinuxGetRusage : public CJsonWebNode<rusage>
{
	public:
		LinuxGetRusage(const std::string & addr);
		virtual void onRequest(const mg_request_info* request_info);
	private:
		rusage data;
};

/*******************  FUNCTION  *********************/
void typeToJson(JsonState & json,std::ostream& stream, const rusage & value);
void typeToJson(JsonState & json,std::ostream& stream, const timeval & value);

};

#endif // LINUXGETRUSAGEJSONWEBNODE_H
