/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstring>
#include <cassert>
#include "WebNode.h"

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*******************  FUNCTION  *********************/
WebNodeData::WebNodeData(void* data, size_t size,const std::string & mimeType,int status,bool autofree)
{
	this->data = data;
	this->size = size;
	this->mimeType = mimeType;
	this->status = status;
	this->autofree = autofree;
}

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

};
