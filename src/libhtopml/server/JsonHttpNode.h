/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_JSON_HTTP_NODE_H
#define HTOPML_JSON_HTTP_NODE_H

/********************  HEADERS  *********************/
#include <sstream>
#include <cstring>
#include "HttpNode.h"
#include "TypeToJson.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
template <class T>
class JsonHttpNode : public HttpNode
{
	public:
		JsonHttpNode(const std::string& path, const T * value);
		virtual void onHttpRequest(HttpResponse & response,const HttpRequest & request);
	protected:
		virtual void onRequest(const HttpRequest & request);
	private:
		const T * value;
};

/*******************  FUNCTION  *********************/
template <class T>
JsonHttpNode<T>::JsonHttpNode(const std::string& path, const T* value)
	: HttpNode(path, true)
{
	this->value = value;
}

/*******************  FUNCTION  *********************/
template <class T>
void JsonHttpNode<T>::onHttpRequest(HttpResponse & response,const HttpRequest & request)
{
	response.setHttpStatus(200);
	response.setMimeType("application/json");
	onRequest(request);
	convertToJson(response.getStream(),*value);
}

/*******************  FUNCTION  *********************/
template <class T>
void JsonHttpNode<T>::onRequest(const HttpRequest & request)
{
	
}

}

#endif // HTOPML_JSON_HTTP_NODE_H
