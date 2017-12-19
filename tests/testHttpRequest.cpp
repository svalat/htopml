/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <string>
#include <cstring>
#include <svUnitTest/svUnitTest.h>
#include <HttpRequest.h>
#include <mongoose.h>

/**********************  USING  *********************/
using namespace std;
using namespace htopml;
using namespace svUnitTest;

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, noUriParam)
{
	mg_request_info mreq;
	mreq.query_string = NULL;
	HttpRequest req(&mreq);
	SVUT_ASSERT_EQUAL("",req.getParam("test"));
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, noUriOneParam)
{
	mg_request_info mreq;
	mreq.query_string = "test=value";
	HttpRequest req(&mreq);
	SVUT_ASSERT_EQUAL("value",req.getParam("test"));
	SVUT_ASSERT_EQUAL("",req.getParam("test2"));
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, noUriMUltiParam)
{
	mg_request_info mreq;
	mreq.query_string = "test=value&test2=value2&test3=value3";
	HttpRequest req(&mreq);
	SVUT_ASSERT_EQUAL("value",req.getParam("test"));
	SVUT_ASSERT_EQUAL("value2",req.getParam("test2"));
	SVUT_ASSERT_EQUAL("value3",req.getParam("test3"));
	SVUT_ASSERT_EQUAL("",req.getParam("test4"));
}



/*******************  FUNCTION  *********************/
SVUT_USE_DEFAULT_MAIN
