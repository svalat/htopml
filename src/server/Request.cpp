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
#include "../../extern-deps/mongoose/mongoose.h"
#include "Request.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
Request::Request(const mg_request_info* mongooseRequest)
{
	assert(mongooseRequest != NULL);
	this->mongooseRequest = mongooseRequest;
}

/*******************  FUNCTION  *********************/
std::string Request::getUri(void ) const
{
	return mongooseRequest->uri;
}

};
