/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_WEB_NODE_H
#define HTOPML_WEB_NODE_H

/********************  HEADERS  *********************/
#include <string>
#include <streambuf>
#include <cstdlib>
#include "Request.h"
#include "Response.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class WebNode
{
	public:
		WebNode(const std::string & path,bool strictPath);
		virtual ~WebNode(void);
		virtual void onHttpRequest(Response & response,const Request & request) = 0;
		virtual WebNode * acceptUri(const char * uri);
		virtual std::string getHomePage(void);
		const std::string & getBasePath(void) const;
	private:
		std::string basePath;
		bool strictPath;
};

};

#endif //HTOPML_WEB_NODE_H
