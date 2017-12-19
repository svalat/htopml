/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_HTTP_REQUEST_H
#define HTOPML_HTTP_REQUEST_H

/********************  HEADERS  *********************/
#include <string>

/*********************  STRUCT  *********************/
struct mg_request_info;
struct mg_connection;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class HttpRequest
{
	public:
		HttpRequest(const mg_request_info * mongooseRequest,std::string auth = "");
		std::string getUri(void) const;
		std::string getAuth(void) const;
		std::string getParam(const std::string & name) const;
	private:
		const mg_request_info * mongooseRequest;
		std::string auth;
};

}

#endif // REQUEST_H
