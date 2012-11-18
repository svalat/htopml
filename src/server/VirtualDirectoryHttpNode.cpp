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
#include "VirtualDirectoryHttpNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
VirtualDirectoryHttpNode::VirtualDirectoryHttpNode(const std::string& mountPoint)
	:HttpNode(mountPoint,false)
{
}

/*******************  FUNCTION  *********************/
VirtualDirectoryHttpNode::~VirtualDirectoryHttpNode(void )
{
    for (HttpNodeVector::iterator it = toAutodelete.begin() ; it != toAutodelete.end() ; ++it)
		delete *it;
}

/*******************  FUNCTION  *********************/
void VirtualDirectoryHttpNode::registerChildNode(HttpNode& node)
{
	registerChildNode(&node,false);
}

/*******************  FUNCTION  *********************/
void VirtualDirectoryHttpNode::registerChildNode(HttpNode* node, bool autodelete)
{
	childs.push_back(node);
	if (autodelete == true)
		toAutodelete.push_back(node);
}

/*******************  FUNCTION  *********************/
HttpNode* VirtualDirectoryHttpNode::acceptUri(const char* uri)
{
	HttpNode * res = HttpNode::acceptUri(uri);
	HttpNode * tmp;
	if (res == NULL)
	{
		return NULL;
	} else {
		for (HttpNodeVector::iterator it = childs.begin() ; it != childs.end() ; ++it)
		{
			tmp = (*it)->acceptUri(uri);
			if (tmp != NULL)
				res = tmp;
		}
		return res;
	}
}

/*******************  FUNCTION  *********************/
void VirtualDirectoryHttpNode::onHttpRequest(HttpResponse & response,const HttpRequest & request)
{
	ostream & str = response.getStream();

	response.setHttpStatus(404);
	response.setMimeType("text/html");
	
	str << "<html><body><ul>";
	for (HttpNodeVector::iterator it = childs.begin() ; it != childs.end() ; ++it)
		str << "<li><a href=\"" << (*it)->getHomePage() << "\">" << (*it)->getHomePage() << "</a>" << endl;
	str << "</ul></body></html>";
}

/*******************  FUNCTION  *********************/
std::string VirtualDirectoryHttpNode::getMountPoint(const std::string& localRelPath) const
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
