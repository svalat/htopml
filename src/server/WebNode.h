/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef IHSTK_WEB_NODE_H
#define IHSTK_WEB_NODE_H

/********************  HEADERS  *********************/
#include <string>
#include <streambuf>
#include <cstdlib>
#include "mongoose.h"

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*********************  STRUCT  *********************/
struct WebNodeData
{
	WebNodeData(void * data,size_t size,const std::string & mimeType,int status = 200,bool autofree=false);
	void * data;
	size_t size;
	std::string mimeType;
	int status;
	bool autofree;
};

/*********************  CLASS  **********************/
class WebNode
{
	public:
		WebNode(const std::string & path,bool strictPath);
		virtual ~WebNode(void);
		virtual WebNodeData getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info) = 0;
		virtual WebNode * acceptUri(const char * uri);
		const std::string & getBasePath(void) const;
	private:
		std::string basePath;
		bool strictPath;
};

};

#endif //IHSTK_WEB_NODE_H
