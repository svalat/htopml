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
#include "HttpResponse.h"
#include "../../extern-deps/mongoose/mongoose.h"

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
	assert(rawData == NULL && rawDataSize == 0);
	if (stringData == NULL)
		stringData = new std::stringstream;
	return *stringData;
}

/*******************  FUNCTION  *********************/
bool HttpResponse::isRawData(void ) const
{
	return (rawData != NULL);
}

/*******************  FUNCTION  *********************/
bool HttpResponse::isStringData(void ) const
{
	return (stringData != NULL);
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
	assert(this->stringData == NULL);
	assert(this->rawData == NULL && this->rawDataSize == 0);
	this->rawData = data;
	this->rawDataSize = size;
	this->freeRawData = autodelete;
	this->status = status;
	if (mimeType != "{KEEP_PREVIOUS}")
		this->mimeType = mimeType;
}

/*******************  FUNCTION  *********************/
void HttpResponse::flushInConnection(mg_connection* conn)
{
	//vars
	void * data;
	size_t size;
	std::string tmp;

	//ensure we get something
	assert (rawData != NULL || stringData != NULL || mongooseFile.empty() == false);

	if (rawData != NULL)
	{
		data = rawData;
		size = rawDataSize;
	} else if (stringData != NULL) {
		//need improvement to avoid tmp copy
		tmp = stringData->str();
		data = (void*)tmp.c_str();
		size = tmp.size();
	} else if (!mongooseFile.empty()) {
		mg_send_file(conn,mongooseFile.c_str());
		return;
	} else {
		abort();
	}
	
	mg_printf(conn,
			"HTTP/1.1 %d OK\r\n"
			"Content-Type: %s\r\n"
			"Content-Length: %lu\r\n" // Always set Content-Length
			"%s\r\n",
			status,mimeType.c_str(),size,extraHeaders.str().c_str());
	mg_write(conn,data,size);
}

/*******************  FUNCTION  *********************/
void HttpResponse::error(int status, const char* format, ... )
{
	//char
	char buffer[1024];

	//format the chain
	va_list param;
	va_start (param, format);
	vsnprintf (buffer,sizeof(buffer), format, param);
	va_end (param);

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
	this->mongooseFile = fname;
}

};
