/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_HTTP_SERVER_H
#define HTOPML_HTTP_SERVER_H

/********************  HEADERS  *********************/
#include <vector>
#include <string>
#include "VirtualDirectoryHttpNode.h"
#include "mongoose.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/********************  ENUM  ************************/
enum HttpServerStatus
{
	SERVER_NOT_STARTED,
	SERVER_STARTING,
	SERVER_RUNNING
};

/*********************  CLASS  **********************/
class HttpServer
{
	public:
		HttpServer(int port);
		virtual ~HttpServer(void);
		void start();
		void stop();
		HttpNode & registerHttpNode(HttpNode & node);
		HttpNode * registerHttpNode(HttpNode * node,bool autodelete = true);
		void setPasswordFile(const std::string & path);
		void quickRegisterFile(const std::string & mountPoint,const std::string & filePath, bool useCache = true,const std::string & mimeType = "auto");
		void setHomepage(const std::string & homepage);
	private:
		mg_context *ctx;
		int port;
		HttpServerStatus status;
	private:
		//copy is forbidden.
		HttpServer(const HttpServer & orig);
		static void * staticCallback(mg_event event,mg_connection *conn);
		void* callback(mg_event event, mg_connection* conn, const mg_request_info* request_info);
		HttpNode * getHttpNode(const char * uri);
		VirtualDirectoryHttpNode rootDir;
		void * quickErrorCode(mg_connection* conn, int code, const std::string& contentType, const std::string& message);
		std::string passFile;
};

};

#endif // HTOPML_HTTP_SERVER_H
