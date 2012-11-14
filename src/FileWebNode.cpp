/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#include <cstdio>
#include <cstring>
#include <pthread.h>
#include "FileWebNode.h"

namespace InternalHtmlSpyToolKit
{

FileWebNode::FileWebNode(const std::string& path, const std::string& filePath, const std::string mimeType)
	: WebNode(path,true)
{
	this->mimeType = mimeType;
	this->filePath = filePath;
	this->cache = NULL;
	this->size = -1;
	pthread_mutex_init(&mutex,NULL);
}

FileWebNode::~FileWebNode(void )
{
	if (cache != NULL)
		free(cache);
	cache = NULL;
	pthread_mutex_destroy(&mutex);
}

void FileWebNode::loadFileInCache(void )
{
	pthread_mutex_lock(&mutex);
	if (cache == NULL)
	{
		FILE * fp = fopen(filePath.c_str(),"r");
		fseek(fp, 0L, SEEK_END);
		size_t fileSize = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		cache = malloc(fileSize);
		this->size = fileSize;
		fread(cache,1,fileSize,fp);
	}
	pthread_mutex_unlock(&mutex);
}

WebNodeData FileWebNode::getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	if (cache == NULL)
		loadFileInCache();
	if (cache != NULL)
	{
		return WebNodeData(cache,size,mimeType);
	} else {
		const char message [] = "Error while loading file.";
		return WebNodeData(strdup(message),sizeof(message),mimeType,404);
	}
}

};
