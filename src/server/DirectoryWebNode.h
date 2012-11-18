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
#include "../server/VirtualDirectoryWebNode.h"
#include "../server/FileWebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  TYPES  **********************/
typedef std::vector<FileWebNode *> FileWebNodeVector;

/*********************  CLASS  **********************/
class DirectoryWebNode : public VirtualDirectoryWebNode
{
	public:
		DirectoryWebNode(const std::string & mountPoint,const std::string & localPath);
		void registerFile(const std::string& localRelPath, const std::string& mimetype = "auto");
	private:
		std::string getLocalPath(const std::string& localRelPath) const;
	private:
		std::string localPath;
};

};

#endif // HTOPML_DIRECTORY_WEB_NODE_H
