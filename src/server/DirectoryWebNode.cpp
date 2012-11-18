/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <sstream>
#include <cstring>
#include "DirectoryWebNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
DirectoryWebNode::DirectoryWebNode(const std::string& mountPoint, const std::string& localPath)
	:VirtualDirectoryWebNode(mountPoint), localPath(localPath)
{
}

/*******************  FUNCTION  *********************/
void DirectoryWebNode::registerFile(const std::string & localRelPath,const std::string & mimetype)
{
	string mountPoint = getMountPoint(localRelPath);
	string localPath = getLocalPath(localRelPath);
	registerChildNode(new FileWebNode(mountPoint,localPath,mimetype),true);
}

/*******************  FUNCTION  *********************/
std::string DirectoryWebNode::getLocalPath(const std::string& localRelPath) const
{
	std::string res(localPath);
	if (res[res.size()-1] != '/' && localRelPath[0] != '/')
		res += '/';
	res += localRelPath;
	return res;
}

};
