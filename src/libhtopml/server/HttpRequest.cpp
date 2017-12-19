/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
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

/*******************  FUNCTION  *********************/
std::string HttpRequest::getParam ( const std::string& name ) const
{
	//trivial
	if (mongooseRequest->query_string == NULL)
		return "";
	
	//prepare
	std::string tmp = name + "=";
	size_t size = tmp.size();
	int pos = 0;
	const char * value = mongooseRequest->query_string;
	
	//search field
	while (value[pos] != '\0') {
		if (strncmp(tmp.c_str(),value + pos,size) == 0)
			break;
		
		//move to next
		while (value[pos] != '\0' && value[pos] != '&')
			pos++;
		
		if (value[pos] != '\0')
			pos++;
	}
	
	//nothing
	if (value[pos] == '\0')
		return "";
	
	//shift
	pos += size;
	
	//move to end
	std::string res;
	while (value[pos] != '\0' && value[pos] != '&') {
		res += value[pos];
		pos++;
	}
	
	return res;
}

}
