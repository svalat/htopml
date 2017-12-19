/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_TEMPLATE_PAGE_HTTP_NODE_H
#define HTOPML_TEMPLATE_PAGE_HTTP_NODE_H

/********************  HEADERS  *********************/
#include "HttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class TemplatePageHttpNode : public HttpNode
{
	public:
		TemplatePageHttpNode(const std::string& mount,const std::string & contentFile,bool cache = false,const std::string & templateFile="");
		virtual void onHttpRequest(HttpResponse & response,const HttpRequest & request);
	protected:
		void load(std::ostream & stream);
	private:
		std::string templateFile;
		std::string contentFile;
		std::string cacheContent;
		bool cache;
};

}

#endif // HTOPML_TEMPLATE_PAGE_HTTP_NODE_H
