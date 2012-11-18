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
FileWebNode::FileWebNode(const std::string& path, const std::string& filePath, const std::string & mimeType)
	: WebNode(path,true), filePath(filePath)
{
	this->cache = NULL;
	this->size = -1;
	pthread_mutex_init(&mutex,NULL);
	if (mimeType == "auto")
		this->mimeType = getMimeType(path);
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
		fclose(fp);
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

/*******************  FUNCTION  *********************/
string FileWebNode::getMimeType(const string& filename)
{
	if (stringFinishBy(filename,".js"))
	{
		return "application/javascript";
	} else if (stringFinishBy(filename,".htm") || stringFinishBy(filename,".html")) {
		return "text/html";
	} else if (stringFinishBy(filename,".css")) {
		return "text/css";
	} else if (stringFinishBy(filename,".json")) {
		return "application/json";
	} else if (stringFinishBy(filename,".png")) {
		return "image/png";
	} else if (stringFinishBy(filename,".jpg")) {
		return "image/jpg";
	} else if (stringFinishBy(filename,".gif")) {
		return "image/gif";
	} else if (stringFinishBy(filename,".svg")) {
		return "image/svg";
	} else if (stringFinishBy(filename,".txt")) {
		return "plain/text";
	} else {
		cerr << "Unknown extension, can't determine mime type automatically : " << filename << endl;
		abort();
	}
}

/*******************  FUNCTION  *********************/
bool FileWebNode::stringFinishBy(const string& value, const string& pattern)
{
	if (value.size() < pattern.size())
		return false;
	else if (strncmp(value.c_str() + value.size() - pattern.size(),pattern.c_str(),pattern.size()) == 0)
		return true;
	else
		return false;
}

};
