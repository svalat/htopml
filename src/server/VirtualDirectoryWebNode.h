/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_VIRTUAL_DIRECTORY_WEB_NODE_H
#define HTOPML_VIRTUAL_DIRECTORY_WEB_NODE_H

/********************  HEADERS  *********************/
#include <vector>
#include "../server/WebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  STRUCT  *********************/
class WebNode;
struct WebNodeData;
typedef std::vector<WebNode*> WebNodeVector;

/*********************  CLASS  **********************/
class VirtualDirectoryWebNode : public WebNode
{
	public:
		VirtualDirectoryWebNode(const std::string & mountPoint);
		virtual ~VirtualDirectoryWebNode(void);
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info);
		virtual WebNode* acceptUri(const char* uri);
		void registerChildNode(WebNode & node);
		void registerChildNode(WebNode * node, bool autodelete = true);
		std::string getMountPoint(const std::string& localRelPath = "") const;
	private:
		WebNodeVector childs;
		WebNodeVector toAutodelete;
};

};

#endif // HTOPML_DIRECTORY_WEB_NODE_H
