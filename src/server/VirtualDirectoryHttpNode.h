/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_VIRTUAL_DIRECTORY_HTTP_NODE_H
#define HTOPML_VIRTUAL_DIRECTORY_HTTP_NODE_H

/********************  HEADERS  *********************/
#include <vector>
#include "../server/HttpNode.h"

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
	private:
		HttpNodeVector childs;
		HttpNodeVector toAutodelete;
};

};

#endif // HTOPML_DIRECTORY_HTTP_NODE_H