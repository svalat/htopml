/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstring>
#include <cassert>
#include <cstdio>
#include "WebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
WebNode::WebNode(const std::string& path, bool strictPath)
{
	this->basePath = path;
	this->strictPath = strictPath;
}

/*******************  FUNCTION  *********************/
WebNode::~WebNode(void )
{

}

/*******************  FUNCTION  *********************/
WebNode * WebNode::acceptUri(const char* uri)
{
	//errors
	assert(uri != NULL);

	//check if string start by
	int len_diff = strlen(uri) - basePath.size();
	int res = strncmp(uri,basePath.c_str(),basePath.size());

	if  (res == 0 && (!strictPath || len_diff == 0))
		return this;
	else
		return NULL;
}

/*******************  FUNCTION  *********************/
const std::string& WebNode::getBasePath(void ) const
{
	return basePath;
}

/*******************  FUNCTION  *********************/
std::string WebNode::getHomePage(void )
{
	return basePath;
}

};
