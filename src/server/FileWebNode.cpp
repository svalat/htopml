/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <iostream>
#include "FileWebNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
FileWebNode::FileWebNode(const std::string& path, const std::string& filePath, const std::string mimeType)
	: WebNode(path,true)
{
	this->mimeType = mimeType;
	this->filePath = filePath;
	this->cache = NULL;
	this->size = -1;
	pthread_mutex_init(&mutex,NULL);
}

/*******************  FUNCTION  *********************/
FileWebNode::~FileWebNode(void )
{
	if (cache != NULL)
		free(cache);
	cache = NULL;
	pthread_mutex_destroy(&mutex);
}

/*******************  FUNCTION  *********************/
void FileWebNode::loadFileInCache(void )
{
	pthread_mutex_lock(&mutex);
	if (cache == NULL)
	{
		FILE * fp = fopen(filePath.c_str(),"r");
		if (fp == NULL)
		{
			cerr << "File not found : " << filePath << endl;
			abort();
		}
		fseek(fp, 0L, SEEK_END);
		size_t fileSize = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		cache = malloc(fileSize);
		this->size = fileSize;
		fread(cache,1,fileSize,fp);
	}
	pthread_mutex_unlock(&mutex);
}

/*******************  FUNCTION  *********************/
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
