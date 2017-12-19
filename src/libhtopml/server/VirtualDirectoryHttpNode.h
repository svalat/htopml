/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_VIRTUAL_DIRECTORY_HTTP_NODE_H
#define HTOPML_VIRTUAL_DIRECTORY_HTTP_NODE_H

/********************  HEADERS  *********************/
#include <vector>
#include "HttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  STRUCT  *********************/
class HttpNode;
struct HttpNodeData;
typedef std::vector<HttpNode*> HttpNodeVector;

/*********************  CLASS  **********************/
class VirtualDirectoryHttpNode : public HttpNode
{
	public:
		VirtualDirectoryHttpNode(const std::string & mountPoint);
		virtual ~VirtualDirectoryHttpNode(void);
		virtual void onHttpRequest(HttpResponse & response,const HttpRequest & request);
		virtual HttpNode* acceptUri(const char* uri);
		void registerChildNode(HttpNode & node);
		void registerChildNode(HttpNode * node, bool autodelete = true);
		std::string getMountPoint(const std::string& localRelPath = "") const;
		void setHomepage(const std::string & homepage);
	private:
		virtual HttpNode* acceptUriIndex(const char* uri);
	private:
		HttpNodeVector childs;
		HttpNodeVector toAutodelete;
		std::string homepage;
};

}

#endif // HTOPML_DIRECTORY_HTTP_NODE_H
