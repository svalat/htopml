/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_SERVER_H
#define HTOPML_SERVER_H

/********************  HEADERS  *********************/
#include <vector>
#include <string>
#include "mongoose.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  STRUCT  *********************/
class WebNode;
struct WebNodeData;
typedef std::vector<WebNode*> WebNodeVector;

/********************  ENUM  ************************/
enum ServerStatus
{
	SERVER_NOT_STARTED,
	SERVER_STARTING,
	SERVER_RUNNING
};

/*********************  CLASS  **********************/
class Server
{
	public:
		Server(int port);
		void start();
		void stop();
		void registerWebNode(WebNode * node);
		void setPasswordFile(const std::string & path);
	private:
		mg_context *ctx;
		int port;
		ServerStatus status;
	private:
		//copy is forbidden.
		Server(const Server & orig);
		static void * staticCallback(mg_event event,mg_connection *conn);
		void* callback(mg_event event, mg_connection* conn, const mg_request_info* request_info);
		WebNode * getWebNode(const char * uri);
		WebNodeVector webNodes;
		void * quickErrorCode(mg_connection* conn, int code, const std::string& contentType, const std::string& message);
		void * quickReturn(mg_connection* conn,const WebNodeData & data);
		std::string passFile;
};

};

#endif // HTOPML_SERVER_H
