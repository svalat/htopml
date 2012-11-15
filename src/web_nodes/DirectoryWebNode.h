/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef DIRECTORYWEBNODE_H
#define DIRECTORYWEBNODE_H

/********************  HEADERS  *********************/
#include <vector>
#include "../server/WebNode.h"
#include "../server/FileWebNode.h"

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
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

#endif // DIRECTORYWEBNODE_H
