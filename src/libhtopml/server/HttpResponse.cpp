/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <cstdarg>
#include <time.h>
#include "HttpResponse.h"
#include "mongoose.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
HttpResponse::HttpResponse(void )
	:mimeType("text/plain")
{
	this->rawData = NULL;
	this->rawDataSize = 0;
	this->stringData = NULL;
	this->freeRawData = false;
	this->status = 200;
	this->type = HTTP_RESPONSE_EMPTY;
}


/*******************  FUNCTION  *********************/
HttpResponse::~HttpResponse(void )
{
	if (stringData != NULL)
		delete stringData;
	if (rawData != NULL && freeRawData == true)
		free(rawData);
}

/*******************  FUNCTION  *********************/
std::ostream& HttpResponse::getStream(void )
{
	assert(rawData == NULL && rawDataSize == 0 && (type == HTTP_RESPONSE_STRING_DATA || type == HTTP_RESPONSE_EMPTY));
	if (stringData == NULL)
	{
		stringData = new std::stringstream;
		type = HTTP_RESPONSE_STRING_DATA;
	}
	return *stringData;
}

/*******************  FUNCTION  *********************/
bool HttpResponse::isRawData(void ) const
{
	return (rawData != NULL && type == HTTP_RESPONSE_RAW_DATA);
}

/*******************  FUNCTION  *********************/
bool HttpResponse::isStringData(void ) const
{
	return (stringData != NULL && type == HTTP_RESPONSE_STRING_DATA);
}

/*******************  FUNCTION  *********************/
void HttpResponse::setMimeType(const char* mimeType)
{
	assert(mimeType != NULL);
	this->mimeType = mimeType;
}

/*******************  FUNCTION  *********************/
void HttpResponse::setMimeType(std::string & mimeType)
{
	this->mimeType = mimeType;
}

/*******************  FUNCTION  *********************/
void HttpResponse::setHttpStatus(int status)
{
	this->status = status;
}

/*******************  FUNCTION  *********************/
void HttpResponse::setRawData(void* data, size_t size,bool autodelete,std::string mimeType,int status)
{
	assert(this->type == HTTP_RESPONSE_EMPTY || this->type == HTTP_RESPONSE_RAW_DATA);
	assert(this->stringData == NULL);
	assert(this->rawData == NULL && this->rawDataSize == 0);
	this->rawData = data;
	this->rawDataSize = size;
	this->freeRawData = autodelete;
	this->status = status;
	if (mimeType != "{KEEP_PREVIOUS}")
		this->mimeType = mimeType;
	this->type = HTTP_RESPONSE_RAW_DATA;
}

/*******************  FUNCTION  *********************/
void HttpResponse::flushInConnection(mg_connection* conn)
{
	//vars
	void * data;
	size_t size;
	std::string tmp;

	switch(this->type)
	{
		case HTTP_RESPONSE_EMPTY:
			this->error(404,"Invalid empty answer");
			break;
		case HTTP_RESPONSE_MONGOOSE_FILE:
			assert(mongooseFile.empty() == false);
			connSendFile(conn,mongooseFile.c_str());
			return;
		case HTTP_RESPONSE_RAW_DATA:
			assert(rawData != NULL);
			data = rawData;
			size = rawDataSize;
			break;
		case HTTP_RESPONSE_STRING_DATA:
			assert(stringData != NULL);
			//need improvement to avoid tmp copy
			tmp = stringData->str();
			data = (void*)tmp.c_str();
			size = tmp.size();
			break;
		case HTTP_RESPONSE_REQUIRE_AUTH:
			connPrintf(conn,
						"HTTP/1.1 401 Unauthorized\r\n"
						"Content-Length: 0\r\n"
						"WWW-Authenticate: Digest qop=\"auth\", "
						"realm=\"%s\", nonce=\"%lu\"\r\n\r\n",
						"htopml",
						(unsigned long) time(NULL));
			break;
		default:
			assert(false);
			abort();
			break;
	}
	
	connPrintf(conn,
			"HTTP/1.1 %d OK\r\n"
			"Content-Type: %s\r\n"
			"Content-Length: %lu\r\n" // Always set Content-Length
			"%s\r\n",
			status,mimeType.c_str(),size,extraHeaders.str().c_str());
	connWrite(conn,data,size);
}

/*******************  FUNCTION  *********************/
void HttpResponse::error(int status, const char* format, ... )
{
	//char
	char buffer[1024];
	
	//setup status
	this->setHttpStatus(status);

	//format the chain
	va_list param;
	va_start (param, format);
	vsnprintf (buffer,sizeof(buffer), format, param);
	va_end (param);

	getStream() << buffer;
}

/*******************  FUNCTION  *********************/
void HttpResponse::printf(const char* format, ... )
{
	//char
	char buffer[1024];

	//format the chain
	va_list param;
	va_start (param, format);
	size_t s = vsnprintf (buffer,sizeof(buffer), format, param);
	va_end (param);
	
	//check
	assert(s < sizeof(buffer) - 1);

	getStream() << buffer;
}

/*******************  FUNCTION  *********************/
void HttpResponse::print(const char* value)
{
	getStream() << value;
}

/*******************  FUNCTION  *********************/
void HttpResponse::setExtraHttpHeader(const std::string& name, const std::string& value)
{
	extraHeaders << "name: " << value << "\r\n";
}

/*******************  FUNCTION  *********************/
void HttpResponse::useMongooseFile(const std::string& fname)
{
	assert(type == HTTP_RESPONSE_EMPTY || type == HTTP_RESPONSE_MONGOOSE_FILE);
	this->mongooseFile = fname;
	this->type = HTTP_RESPONSE_MONGOOSE_FILE;
}

/*******************  FUNCTION  *********************/
void HttpResponse::requireAuth(void )
{
	assert(type == HTTP_RESPONSE_EMPTY || type == HTTP_RESPONSE_REQUIRE_AUTH);
	type = HTTP_RESPONSE_REQUIRE_AUTH;
}

/*******************  FUNCTION  *********************/
int HttpResponse::getHttpStatus(void ) const
{
	return this->status;
}

/*******************  FUNCTION  *********************/
const std::string& HttpResponse::getMimeType(void ) const
{
	return this->mimeType;
}

/*******************  FUNCTION  *********************/
HttpResponseType HttpResponse::getType(void ) const
{
	return this->type;
}

/*******************  FUNCTION  *********************/
void HttpResponse::connSendFile(mg_connection* conn, const std::string& path)
{
	mg_send_file(conn,path.c_str());
}

/*******************  FUNCTION  *********************/
void HttpResponse::connWrite(mg_connection* conn, void* data, size_t size)
{
	mg_write(conn,data,size);
}

/*******************  FUNCTION  *********************/
void HttpResponse::connPrintf(mg_connection* conn, const char* format, ... )
{
	//char
	char buffer[1024];

	//format the chain
	va_list param;
	va_start (param, format);
	size_t s = vsnprintf (buffer,sizeof(buffer), format, param);
	va_end (param);
	
	//check
	assert(s < sizeof(buffer) - 1);
	
	//write
	connWrite(conn,buffer,s);
}

}
