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
#include <cstring>
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
HttpServer::HttpServer(int port,const std::string & listenAddr)
	:rootDir("/")
{
	//errors
	assert(port > 0 && port <= 65000);

	//setup defaults
	this->port = port;
	this->ctx = NULL;
	this->status = SERVER_NOT_STARTED;
	this->authContext = "htopml";
	this->listenAddr = listenAddr;
}

/*******************  FUNCTION  *********************/
HttpServer::~HttpServer(void )
{
	if (this->status == SERVER_RUNNING && this->ctx != NULL)
		this->stop();
}

/*******************  FUNCTION  *********************/
bool HttpServer::start()
{
	//errors
	assert(status == SERVER_NOT_STARTED);

	//mark as starting
	status = SERVER_STARTING;
	
	//generate tmp string
	string port;
	if (listenAddr.empty() == false)
		port += listenAddr + ":";
	port += toString(this->port);

	//gen options
	const char *options[11] = {"listening_ports", port.c_str(), "num_threads", "1" ,"error_log_file","mongoose.err.log","authentication_domain","htopml", NULL, NULL, NULL};
	int cntOptions = 8;

	//optional onces.
	//TODO need to check how to use, but mongoose maybe manage pass with a cache, so may be ok (but failed)
	/*if (passFile.empty() == false)
	{
		options[cntOptions++] = "global_passwords_file";
		options[cntOptions++] = passFile.c_str();
	}*/
	if (!passFile.empty())
		loadAuthCache();

	//start the server
	ctx = mg_start(&staticCallback, this, options);
	//assert(ctx != NULL);

	//mark as starting
	if (ctx != NULL)
	{
		status = SERVER_RUNNING;
		return true;
	} else {
		status = SERVER_NOT_STARTED;
		return false;
	}
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
void HttpServer::loadAuthCache(void )
{
	//buffers
	char login[1024];
	char domain[1024];
	char pass[1024];
	char buffer[4096];
	int line = 1;

	//clear current cache
	authCache.clear();
	//open file
	FILE * fp = fopen(passFile.c_str(),"r");
	if (fp == NULL)
	{
		perror(passFile.c_str());
		abort();
	}
	//load entries
	while (!feof(fp))
	{
		if (fgets(buffer,sizeof(buffer),fp) <= 0)
		{
			break;
		} else if (*buffer == '\n') {
			continue;
		} else if (sscanf(buffer,"%[^:]:%[^:]:%s\n",login,domain,pass) == 3) {
			if (strcmp(domain,"htopml"))
				fprintf(stderr,"Warning : your pass file (%s) contain and invalid entry line %d : invalid domain (%s).\n",passFile.c_str(),line,domain);
			else
				authCache[login] = pass;
		} else {
			fprintf(stderr,"Warning : your pass file (%s) contain and invalid entry line %d : invalid line format (%s).\n",passFile.c_str(),line,buffer);
		}
		line++;
	}
}

/*******************  FUNCTION  *********************/
string HttpServer::getLoginPass(string login) const
{
	HttpServerAuthCache::const_iterator it = authCache.find(login);
	if (it == authCache.end())
		return "";
	else
		return it->second;
}

/*******************  FUNCTION  *********************/
string HttpServer::getConnAuth(mg_connection* conn) const
{
	struct mg_auth_header ah;
	char line[256], f_user[256], ha1[256], f_domain[256], buf[8192], *p;

	if (!mg_parse_auth_header(conn, buf, sizeof(buf), &ah))
		return "";

	if (ah.user == NULL || *ah.user == '\0')
		return "";

	string pass = getLoginPass(ah.user);
    if (!pass.empty())
	{
		if (mg_check_password(conn, pass.c_str(), ah.uri,ah.nonce, ah.nc, ah.cnonce, ah.qop, ah.response))
			return ah.user;
		else
			fprintf(stderr,"Caution, get an invalid access on htopml from : XXX.XXX.XXX.XXX\n");//,mg_get_request_info(conn)->remote_ip);
	}

	return "";
}

/*******************  FUNCTION  *********************/
void * HttpServer::callback(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	//vars
	HttpRequest req(request_info,getConnAuth(conn));
	HttpResponse rep;

	//todo improve to made auth every time optional
	if (authContext.empty() == false && passFile.empty() == false && req.getAuth().empty())
	{
		rep.requireAuth();
		rep.flushInConnection(conn);
		return (void*)"";
	} else {
		if (event == MG_NEW_REQUEST) {
			//search web node
			HttpNode * node = getHttpNode(request_info->uri);
			if (node == NULL)
			{
				return quickErrorCode(conn,404,"text/plain","Page not found\n");
			} else {
				node->onHttpRequest(rep,req);
				rep.flushInConnection(conn);
				return (void*)"";
			}
		} else {
			return NULL;
		}
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
void * HttpServer::quickErrorCode(mg_connection* conn,int code, const string& contentType, const string& message)
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
void HttpServer::setPasswordFile(const string& path)
{
	this->passFile = path;
}

/*******************  FUNCTION  *********************/
void HttpServer::quickRegisterFile(const string& mountPoint, const string& filePath, bool useCache, const string& mimeType)
{
	registerHttpNode(new FileHttpNode(mountPoint,filePath,useCache,mimeType),true);
}

}
