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
#include "VirtualDirectoryWebNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
VirtualDirectoryWebNode::VirtualDirectoryWebNode(const std::string& mountPoint)
	:WebNode(mountPoint,false)
{
}

/*******************  FUNCTION  *********************/
VirtualDirectoryWebNode::~VirtualDirectoryWebNode(void )
{
    for (WebNodeVector::iterator it = toAutodelete.begin() ; it != toAutodelete.end() ; ++it)
		delete *it;
}

/*******************  FUNCTION  *********************/
void VirtualDirectoryWebNode::registerChildNode(WebNode& node)
{
	registerChildNode(&node,false);
}

/*******************  FUNCTION  *********************/
void VirtualDirectoryWebNode::registerChildNode(WebNode* node, bool autodelete)
{
	childs.push_back(node);
	if (autodelete == true)
		toAutodelete.push_back(node);
}

/*******************  FUNCTION  *********************/
WebNode* VirtualDirectoryWebNode::acceptUri(const char* uri)
{
	WebNode * res = WebNode::acceptUri(uri);
	WebNode * tmp;
	if (res == NULL)
	{
		return NULL;
	} else {
		for (WebNodeVector::iterator it = childs.begin() ; it != childs.end() ; ++it)
		{
			tmp = (*it)->acceptUri(uri);
			if (tmp != NULL)
				res = tmp;
		}
		return res;
	}
}

/*******************  FUNCTION  *********************/
WebNodeData VirtualDirectoryWebNode::getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	stringstream str;
	str << "<html><body><ul>";
	for (WebNodeVector::iterator it = childs.begin() ; it != childs.end() ; ++it)
		str << "<li><a href=\"" << (*it)->getHomePage() << "\">" << (*it)->getHomePage() << "</a>" << endl;
	str << "</ul></body></html>";
	//TODO generate a file list here.
	char * res = strdup(str.str().c_str());
	return WebNodeData(res,strlen(res),"text/html",404,true);
}

/*******************  FUNCTION  *********************/
std::string VirtualDirectoryWebNode::getMountPoint(const std::string& localRelPath) const
{
	std::string res(getBasePath());

	if (localRelPath.empty() == false)
	{
		if (res[res.size()-1] != '/' && localRelPath[0] != '/')
			res += '/';
		res += localRelPath;
	}
	return res;
}

};
