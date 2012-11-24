/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cassert>
#include <mongoose.h>
#include "Common.h"
#include "HttpNode.h"
#include "HttpServer.h"
#include "FileHttpNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
HttpServer::HttpServer(int port)
	:rootDir("/")
{
	//errors
	assert(port > 0 && port <= 65000);

	//setup defaults
	this->port = port;
	this->ctx = NULL;
	this->status = SERVER_NOT_STARTED;
}

/*******************  FUNCTION  *********************/
HttpServer::~HttpServer(void )
{
	if (this->status == SERVER_RUNNING && this->ctx != NULL)
		this->stop();
}

/*******************  FUNCTION  *********************/
void HttpServer::start()
{
	//errors
	assert(status == SERVER_NOT_STARTED);

	//mark as starting
	status = SERVER_STARTING;
	
	//generate tmp string
	string port = toString(this->port);

	//gen options
	const char *options[5] = {"listening_ports", port.c_str(), NULL, NULL, NULL};
	int cntOptions = 2;

	//optional onces.
	if (passFile.empty() == false)
	{
		options[cntOptions++] = "put_delete_passwords_file";
		options[cntOptions++] = passFile.c_str();
	}

	//start the server
	ctx = mg_start(&staticCallback, this, options);

	//mark as starting
	status = SERVER_RUNNING;
}

/*******************  FUNCTION  *********************/
void HttpServer::stop()
{
	assert(status == SERVER_RUNNING && ctx != NULL);
	mg_stop(ctx);
	this->ctx = NULL;
}

/*******************  FUNCTION  *********************/
void* HttpServer::staticCallback(mg_event event, mg_connection* conn)
{
	const struct mg_request_info *request_info = mg_get_request_info(conn);
	HttpServer * server = (HttpServer*)request_info->user_data;
	return server->callback(event,conn,request_info);
}

/*******************  FUNCTION  *********************/
void * HttpServer::callback(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	if (event == MG_NEW_REQUEST) {
		//search web node
		HttpNode * node = getHttpNode(request_info->uri);
		if (node == NULL)
		{
			return quickErrorCode(conn,404,"text/plain","Page not found\n");
		} else {
			HttpRequest req(request_info);
			HttpResponse rep;
			node->onHttpRequest(rep,req);
			rep.flushInConnection(conn);
			return (void*)"";
		}
	} else {
		return NULL;
	}
}

/*******************  FUNCTION  *********************/
void HttpServer::setHomepage(const string& homepage)
{
	rootDir.setHomepage(homepage);
}

/*******************  FUNCTION  *********************/
HttpNode & HttpServer::registerHttpNode(HttpNode& node)
{
	rootDir.registerChildNode(node);
	return node;
}

/*******************  FUNCTION  *********************/
HttpNode * HttpServer::registerHttpNode(htopml::HttpNode* node, bool autodelete)
{
	rootDir.registerChildNode(node,autodelete);
	return node;
}

/*******************  FUNCTION  *********************/
HttpNode* HttpServer::getHttpNode(const char* uri)
{
	//errors
	assert(uri != NULL);
	HttpNode * res = NULL;

	//loop on all nodes to find the addr
	res = rootDir.acceptUri(uri);

	return res;
}

/*******************  FUNCTION  *********************/
void * HttpServer::quickErrorCode(mg_connection* conn,int code, const std::string& contentType, const std::string& message)
{
	mg_printf(conn,
			"HTTP/1.1 %d OK\r\n"
			"Content-Type: %s\r\n"
			"Content-Length: %lu\r\n" // Always set Content-Length
			"\r\n"
			"%s",
			code,contentType.c_str(),message.size(),message.c_str());

	// Mark as processed
	return (void*)("");
}

/*******************  FUNCTION  *********************/
void HttpServer::setPasswordFile(const std::string& path)
{
	this->passFile = path;
}

/*******************  FUNCTION  *********************/
void HttpServer::quickRegisterFile(const string& mountPoint, const string& filePath, bool useCache, const string& mimeType)
{
	registerHttpNode(new FileHttpNode(mountPoint,filePath,useCache,mimeType),true);
}

}
