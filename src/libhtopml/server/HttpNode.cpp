/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstring>
#include <cassert>
#include <cstdio>
#include "HttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
HttpNode::HttpNode(const std::string& path, bool strictPath)
{
	this->basePath = path;
	this->strictPath = strictPath;
}

/*******************  FUNCTION  *********************/
HttpNode::~HttpNode(void )
{

}

/*******************  FUNCTION  *********************/
HttpNode * HttpNode::acceptUri(const char* uri)
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
const std::string& HttpNode::getBasePath(void ) const
{
	return basePath;
}

/*******************  FUNCTION  *********************/
std::string HttpNode::getHomePage(void )
{
	return basePath;
}

}
