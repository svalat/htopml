/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cassert>
#include "Common.h"
#include "WebNode.h"
#include "Server.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*******************  FUNCTION  *********************/
Server::Server(int port)
{
	//errors
	assert(port > 0 && port <= 65000);

	//setup defaults
	this->port = port;
	this->ctx = NULL;
	this->status = SERVER_NOT_STARTED;
}

/*******************  FUNCTION  *********************/
void Server::start()
{
	//errors
	assert(status == SERVER_NOT_STARTED);

	//mark as starting
	status = SERVER_STARTING;
	
	//generate tmp string
	string port = toString(this->port);

	//gen options
	const char *options[] = {"listening_ports", port.c_str(), NULL};

	//start the server
	ctx = mg_start(&staticCallback, this, options);

	//mark as starting
	status = SERVER_RUNNING;
}

/*******************  FUNCTION  *********************/
void Server::stop()
{
	assert(status == SERVER_RUNNING && ctx != NULL);
	mg_stop(ctx);
}

/*******************  FUNCTION  *********************/
void* Server::staticCallback(mg_event event, mg_connection* conn)
{
	const struct mg_request_info *request_info = mg_get_request_info(conn);
	Server * server = (Server*)request_info->user_data;
	return server->callback(event,conn,request_info);
}

/*******************  FUNCTION  *********************/
void * Server::callback(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	if (event == MG_NEW_REQUEST) {
		//search web node
		WebNode * node = getWebNode(request_info->uri);
		if (node == NULL)
		{
			return quickErrorCode(conn,404,"text/plain","Page not found\n");
		} else {
			WebNodeData data = node->getContent(event,conn,request_info);
			quickReturn(conn,data);
			if (data.autofree)
				free(data.data);
			return (void*)"";
		}
	} else {
		return NULL;
	}
}

/*******************  FUNCTION  *********************/
void Server::registerWebNode(WebNode* node)
{
	this->webNodes.push_back(node);
}

/*******************  FUNCTION  *********************/
WebNode* Server::getWebNode(const char* uri)
{
	//errors
	assert(uri != NULL);
	WebNode * res = NULL;

	//loop on all nodes to find the addr
	for (WebNodeVector::iterator it = webNodes.begin() ; it != webNodes.end() ; ++it)
	{
		WebNode * tmp = (*it)->acceptUri(uri);
		if (tmp != NULL)
			res = tmp;
	}

	return res;
}

/*******************  FUNCTION  *********************/
void * Server::quickReturn(mg_connection* conn, const WebNodeData& data)
{
	mg_printf(conn,
			"HTTP/1.1 %d OK\r\n"
			"Content-Type: %s\r\n"
			"Content-Length: %lu\r\n" // Always set Content-Length
			"\r\n",
			data.status,data.mimeType.c_str(),data.size);
	mg_write(conn,data.data,data.size);

	// Mark as processed
	return (void*)("");
}

/*******************  FUNCTION  *********************/
void * Server::quickErrorCode(mg_connection* conn,int code, const std::string& contentType, const std::string& message)
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

}
