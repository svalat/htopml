/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_MOCK_HTTP_NODE_H
#define HTOPML_MOCK_HTTP_NODE_H

/********************  HEADERS  *********************/
#include <ValidationHttpNode.h>
#include <mongoose.h>

/**********************  USING  *********************/
using namespace std;
using namespace htopml;
using namespace svUnitTest;

/*******************  FUNCTION  *********************/
class MockHttpResponse : public HttpResponse
{
	public:
		stringstream buffer;
	protected:
		virtual void connSendFile(mg_connection* conn, const string& path)
		{
			buffer << "MONGOOSE SEND FILE " << path << endl;
		}
		virtual void connWrite(mg_connection* conn, void* data, size_t size)
		{
			if (data != NULL && size > 0)
				buffer << (const char*) data;	
		}
};

#endif //HTOPML_MOCK_HTTP_NODE_H
