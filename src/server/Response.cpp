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
#include "Response.h"
#include "../../extern-deps/mongoose/mongoose.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
Response::Response(void )
	:mimeType("text/plain")
{
	this->rawData = NULL;
	this->rawDataSize = 0;
	this->stringData = NULL;
	this->freeRawData = false;
	this->status = 200;
}


/*******************  FUNCTION  *********************/
Response::~Response(void )
{
	if (stringData != NULL)
		delete stringData;
	if (rawData != NULL && freeRawData == true)
		free(rawData);
}

/*******************  FUNCTION  *********************/
std::ostream& Response::getStream(void )
{
	assert(rawData == NULL && rawDataSize == 0);
	if (stringData == NULL)
		stringData = new std::stringstream;
	return *stringData;
}

/*******************  FUNCTION  *********************/
bool Response::isRawData(void ) const
{
	return (rawData != NULL);
}

/*******************  FUNCTION  *********************/
bool Response::isStringData(void ) const
{
	return (stringData != NULL);
}

/*******************  FUNCTION  *********************/
void Response::setMimeType(const char* mimeType)
{
	assert(mimeType != NULL);
	this->mimeType = mimeType;
}

/*******************  FUNCTION  *********************/
void Response::setMimeType(std::string & mimeType)
{
	this->mimeType = mimeType;
}

/*******************  FUNCTION  *********************/
void Response::setHttpStatus(int status)
{
	this->status = status;
}

/*******************  FUNCTION  *********************/
void Response::setRawData(void* data, size_t size,bool autodelete,std::string mimeType,int status)
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
void Response::flushInConnection(mg_connection* conn)
{
	//vars
	void * data;
	size_t size;
	std::string tmp;

	//ensure we get something
	assert (rawData != NULL || stringData != NULL);

	if (rawData != NULL)
	{
		data = rawData;
		size = rawDataSize;
	} else if (stringData != NULL) {
		//need improvement to avoid tmp copy
		tmp = stringData->str();
		data = (void*)tmp.c_str();
		size = tmp.size();
	} else {
		abort();
	}
	
	mg_printf(conn,
			"HTTP/1.1 %d OK\r\n"
			"Content-Type: %s\r\n"
			"Content-Length: %lu\r\n" // Always set Content-Length
			"\r\n",
			status,mimeType.c_str(),size);
	mg_write(conn,data,size);
}

/*******************  FUNCTION  *********************/
void Response::error(int status, const char* format, ... )
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
void Response::print(const char* value)
{
	getStream() << value;
}

};
