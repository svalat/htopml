/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <iostream>
#include <cassert>
#include "FileHttpNode.h"
#include "mongoose.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
FileHttpNode::FileHttpNode(const std::string& path, const std::string& filePath, bool useCache, const std::string & mimeType)
	: HttpNode(path,true), filePath(filePath)
{
	this->cache = NULL;
	this->size = -1;
	pthread_mutex_init(&mutex,NULL);
	if (mimeType == "auto")
		this->mimeType = getMimeType(filePath);
	this->useCache = useCache;
}

/*******************  FUNCTION  *********************/
FileHttpNode::~FileHttpNode(void )
{
	if (cache != NULL)
		free(cache);
	cache = NULL;
	pthread_mutex_destroy(&mutex);
}

/*******************  FUNCTION  *********************/
void FileHttpNode::loadFileInCache(void )
{
	size_t res;
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
		res = fread(cache,1,fileSize,fp);
		assert(res == fileSize);
		fclose(fp);
	}
	pthread_mutex_unlock(&mutex);
}

/*******************  FUNCTION  *********************/
void FileHttpNode::onHttpRequest(HttpResponse & response,const HttpRequest & request)
{
	response.useMongooseFile(filePath);
	/*if (cache == NULL)
		loadFileInCache();

	if (cache != NULL)
	{
		response.setMimeType(mimeType);
		response.setRawData(cache,size,!useCache);
		if (useCache == false)
			cache = NULL;
	} else {
		response.setMimeType("text/html");
		response.setHttpStatus(404);
		response.print("Error while loading file.");
	}*/
}

/*******************  FUNCTION  *********************/
string FileHttpNode::getMimeType(const string& filename)
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
	} else if (stringFinishBy(filename,".xml")) {
		return "text/xml";
	} else {
		cerr << "Unknown extension, can't determine mime type automatically : " << filename << endl;
		abort();
	}
}

/*******************  FUNCTION  *********************/
bool FileHttpNode::stringFinishBy(const string& value, const string& pattern)
{
	if (value.size() < pattern.size())
		return false;
	else if (strncmp(value.c_str() + value.size() - pattern.size(),pattern.c_str(),pattern.size()) == 0)
		return true;
	else
		return false;
}

}
