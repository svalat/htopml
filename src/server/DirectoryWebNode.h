/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_DIRECTORY_WEB_NODE_H
#define HTOPML_DIRECTORY_WEB_NODE_H

/********************  HEADERS  *********************/
#include <vector>
#include "../server/WebNode.h"
#include "../server/FileWebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  TYPES  **********************/
typedef std::vector<FileWebNode *> FileWebNodeVector;

/*********************  CLASS  **********************/
class DirectoryWebNode : public WebNode
{
	public:
		DirectoryWebNode(const std::string & webMountPoint,const std::string & localPath);
		virtual ~DirectoryWebNode(void);
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info);
		virtual WebNode* acceptUri(const char* uri);
		void registerFile(const std::string localRelPath,const std::string mimetype);
	private:
		std::string getWebMountPoint(const std::string& localRelPath) const;
		std::string getLocalPath(const std::string& localRelPath) const;
	private:
		std::string webMountPoint;
		std::string localPath;
		FileWebNodeVector files;
};

};

#endif // HTOPML_DIRECTORY_WEB_NODE_H
