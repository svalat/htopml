/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_HTTP_REQUEST_H
#define HTOPML_HTTP_REQUEST_H

/********************  HEADERS  *********************/
#include <string>

/*********************  STRUCT  *********************/
struct mg_request_info;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class HttpRequest
{
	public:
		HttpRequest(const mg_request_info * mongooseRequest);
		std::string getUri(void) const;
	private:
		const mg_request_info * mongooseRequest;
};

};

#endif // REQUEST_H
