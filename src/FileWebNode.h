/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef IHSTKWEBNODEFILE_H
#define IHSTKWEBNODEFILE_H

#include "WebNode.h"

namespace InternalHtmlSpyToolKit
{

class FileWebNode : public WebNode
{
	public:
		FileWebNode(const std::string& path, const std::string & filePath,const std::string mimeType);
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

#endif // IHSTKWEBNODEFILE_H
