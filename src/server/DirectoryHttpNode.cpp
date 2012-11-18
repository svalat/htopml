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
#include "DirectoryHttpNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
DirectoryHttpNode::DirectoryHttpNode(const std::string& mountPoint, const std::string& localPath)
	:VirtualDirectoryHttpNode(mountPoint), localPath(localPath)
{
}

/*******************  FUNCTION  *********************/
void DirectoryHttpNode::registerFile(const std::string & localRelPath,bool useCache,const std::string & mimetype)
{
	string mountPoint = getMountPoint(localRelPath);
	string localPath = getLocalPath(localRelPath);
	registerChildNode(new FileHttpNode(mountPoint,localPath,useCache,mimetype),true);
}

/*******************  FUNCTION  *********************/
std::string DirectoryHttpNode::getLocalPath(const std::string& localRelPath) const
{
	std::string res(localPath);
	if (res[res.size()-1] != '/' && localRelPath[0] != '/')
		res += '/';
	res += localRelPath;
	return res;
}

};
