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
DirectoryWebNode::DirectoryWebNode(const std::string& webMountPoint, const std::string& localPath)
	:WebNode(webMountPoint,false), webMountPoint(webMountPoint), localPath(localPath)
{
}

/*******************  FUNCTION  *********************/
DirectoryWebNode::~DirectoryWebNode(void )
{
    for (FileWebNodeVector::iterator it = files.begin() ; it != files.end() ; ++it)
		delete *it;
}

/*******************  FUNCTION  *********************/
void DirectoryWebNode::registerFile(const std::string & localRelPath,const std::string & mimetype)
{
	FileWebNode * node = new FileWebNode(getWebMountPoint(localRelPath),getLocalPath(localRelPath),mimetype);
	files.push_back(node);
}

/*******************  FUNCTION  *********************/
WebNode* DirectoryWebNode::acceptUri(const char* uri)
{
	WebNode * res = WebNode::acceptUri(uri);
	if (res == NULL)
	{
		return NULL;
	} else {
		for (FileWebNodeVector::iterator it = files.begin() ; it != files.end() ; ++it)
			if ((*it)->acceptUri(uri))
				res = *it;
		return res;
	}
}

/*******************  FUNCTION  *********************/
WebNodeData DirectoryWebNode::getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	stringstream str;
	str << "<html><body><ul>";
	for (FileWebNodeVector::iterator it = files.begin() ; it != files.end() ; ++it)
		str << "<li><a href=\"" << (*it)->getHomePage() << "\">" << (*it)->getHomePage() << "</a>" << endl;
	str << "</ul></body></html>";
	//TODO generate a file list here.
	char * res = strdup(str.str().c_str());
	return WebNodeData(res,strlen(res),"text/html",404,true);
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

/*******************  FUNCTION  *********************/
std::string DirectoryWebNode::getWebMountPoint(const std::string& localRelPath) const
{
	std::string res(webMountPoint);
	if (res[res.size()-1] != '/' && localRelPath[0] != '/')
		res += '/';
	res += localRelPath;
	return res;
}

};
