/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_FILE_HTTP_NODE_H
#define HTOPML_FILE_HTTP_NODE_H

/********************  HEADERS  *********************/
#include "HttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class FileHttpNode : public HttpNode
{
	public:
		FileHttpNode(const std::string& path, const std::string & filePath,bool useCache = true,const std::string & mimeType = "auto");
		virtual ~FileHttpNode(void );
		virtual void onHttpRequest(HttpResponse & response,const HttpRequest & request);
		static std::string getMimeType(const std::string & filename);
	private:
		FileHttpNode(const FileHttpNode & node);
		void loadFileInCache(void);
		static bool stringFinishBy(const std::string & value,const std::string & pattern);
	private:
		std::string filePath;
		std::string mimeType;
		void * cache;
		size_t size;
		pthread_mutex_t mutex;
		bool useCache;
};

}

#endif // HTOPML_FILE_HTTP_NODE_H
