/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_HTTP_RESPONSE_H
#define HTOPML_HTTP_RESPONSE_H

/********************  HEADERS  *********************/
#include <string>
#include <sstream>
#include <ostream>

/*********************  STRUCT  *********************/
struct mg_connection;

/********************  NAMESPACE  *******************/
namespace htopml
{

enum HttpResponseType
{
	HTTP_RESPONSE_RAW_DATA,
	HTTP_RESPONSE_MONGOOSE_FILE,
	HTTP_RESPONSE_STRING_DATA,
	HTTP_RESPONSE_REQUIRE_AUTH,
	HTTP_RESPONSE_EMPTY
};

/*********************  CLASS  **********************/
class HttpResponse
{
	public:
		HttpResponse(void);
		virtual ~HttpResponse(void);
		void setMimeType(const char * mimeType);
		void setMimeType(std::string & mimeType);
		void setRawData(void * data,size_t size,bool autodelete,std::string mimeType = "{KEEP_PREVIOUS}",int status = 200);
		void setHttpStatus(int status);
		std::ostream & getStream(void);
		bool isRawData(void) const;
		bool isStringData(void) const;
		void flushInConnection(mg_connection* conn);
		void printf(const char * format,...);
		void print(const char * format);
		void error(int status,const char * format,...);
		void errorHtml(int status,const char *test,...);
		void setInfo(int status,const std::string & mimeType);
		void setExtraHttpHeader(const std::string & name,const std::string & value);
		void useMongooseFile(const std::string & fname);
		void requireAuth(void);
		HttpResponseType getType(void) const;
		const std::string & getMimeType(void) const;
		int getHttpStatus(void) const;
	protected:
		virtual void connSendFile(mg_connection* conn,const std::string & path);
		virtual void connWrite(mg_connection* conn,void* data, size_t size);
		virtual void connPrintf(mg_connection* conn,const char * format,...);
	private:
		/** Copy is not supported. **/
		HttpResponse(const HttpResponse & response);
	private:
		HttpResponseType type;
		std::string mimeType;
		void * rawData;
		size_t rawDataSize;
		std::stringstream * stringData;
		bool freeRawData;
		int status;
		std::stringstream extraHeaders;
		std::string mongooseFile;
};

}

#endif // HTOPML_HTTP_RESPONSE_H
