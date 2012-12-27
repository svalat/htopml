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
#include <cstring>
#include "mongoose.h"
#include "HttpRequest.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
HttpRequest::HttpRequest(const mg_request_info* mongooseRequest,std::string auth)
{
	assert(mongooseRequest != NULL);
	this->mongooseRequest = mongooseRequest;
	this->auth = auth;
}

/*******************  FUNCTION  *********************/
std::string HttpRequest::getUri(void ) const
{
	return mongooseRequest->uri;
}

/*******************  FUNCTION  *********************/
std::string HttpRequest::getAuth(void ) const
{
	return auth;
}

}
