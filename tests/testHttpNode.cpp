/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <string>
#include <cstring>
#include <svUnitTest/svUnitTest.h>
#include <ValidationHttpNode.h>

/**********************  USING  *********************/
using namespace std;
using namespace htopml;
using namespace svUnitTest;

/*********************  CONSTS  *********************/
// static const std::string TEST_STRING_1 = "This is a test to load quicly a file in memory to send it to user as http anwser.\n";

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
	HttpResponse response;
	SVUT_ASSERT_TODO("todo");
}

/*******************  FUNCTION  *********************/
SVUT_USE_DEFAULT_MAIN
