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
#include <ValidationHttpNode.h>
#include <mongoose.h>
#include "mocks/MockHttpNode.h"

/**********************  USING  *********************/
using namespace std;
using namespace htopml;
using namespace svUnitTest;

/*********************  CONSTS  *********************/
static const std::string TEST_STRING_1 = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 41\r\n\r\nOk, get the page at URI : /test/test.txt\n";

/*******************  FUNCTION  *********************/
static HttpNode * node = NULL;

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_SETUP(HttpNode)
{
	node = new ValidationHttpNode("/test/test.txt",true);
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEAR_DOWN(HttpNode)
{
	if (node != NULL)
		delete node;
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, acceptUri_good)
{
	HttpNode * res = node->acceptUri("/test/test.txt");
	SVUT_ASSERT_SAME(node,res);
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, acceptUri_bad1)
{
	HttpNode * res = node->acceptUri("/test/test.txt1");
	SVUT_ASSERT_NULL(res);
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, acceptUri_bad2)
{
	HttpNode * res = node->acceptUri("/test/test.tx");
	SVUT_ASSERT_NULL(res);
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, acceptUri_nostrict_good)
{
	ValidationHttpNode node("/test/",false);
	HttpNode * res = node.acceptUri("/test/test.txt");
	SVUT_ASSERT_SAME(&node,res);
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, acceptUri_nostrict_false)
{
	ValidationHttpNode node("/test/",false);
	HttpNode * res = node.acceptUri("/tests/test.txt");
	SVUT_ASSERT_NULL(res);
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, getHomePage)
{
	SVUT_ASSERT_EQUAL("/test/test.txt",node->getHomePage());
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, getBasePath)
{
	SVUT_ASSERT_EQUAL("/test/test.txt",node->getBasePath());
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(HttpNode, onRequest)
{
	MockHttpResponse response;
	mg_request_info info;
	info.uri = "/test/test.txt";
	HttpRequest request(&info,"testuser");
	node->onHttpRequest(response,request);
	response.flushInConnection(NULL);
	SVUT_ASSERT_EQUAL(TEST_STRING_1,response.buffer.str());
}

/*******************  FUNCTION  *********************/
SVUT_USE_DEFAULT_MAIN
