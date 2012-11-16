/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_FILE_WEB_NODE_H
#define HTOPML_FILE_WEB_NODE_H

/********************  HEADERS  *********************/
#include "WebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class FileWebNode : public WebNode
{
	public:
		FileWebNode(const std::string& path, const std::string & filePath,const std::string & mimeType);
		virtual ~FileWebNode(void );
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info);
	private:
		FileWebNode(const FileWebNode & node);
		void loadFileInCache(void);
	private:
		std::string filePath;
		std::string mimeType;
		void * cache;
		size_t size;
		pthread_mutex_t mutex;
};

};

#endif // HTOPML_FILE_WEB_NODE_H
