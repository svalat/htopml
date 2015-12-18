/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_HTTP_NODE_H
#define HTOPML_HTTP_NODE_H

/********************  HEADERS  *********************/
#include <string>
#include <streambuf>
#include <cstdlib>
#include "HttpRequest.h"
#include "HttpResponse.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class HttpNode
{
	public:
		HttpNode(const std::string & path,bool strictPath);
		virtual ~HttpNode(void);
		virtual void onHttpRequest(HttpResponse & response,const HttpRequest & request) = 0;
		virtual HttpNode * acceptUri(const char * uri);
		virtual std::string getHomePage(void);
		const std::string & getBasePath(void) const;
	private:
		std::string basePath;
		bool strictPath;
};

}

#endif //HTOPML_HTTP_NODE_H
