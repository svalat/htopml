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
#include <Common.h>

/**********************  USING  *********************/
using namespace std;
using namespace htopml;
using namespace svUnitTest;

/*********************  CONSTS  *********************/
static const std::string TEST_STRING_1 = "This is a test to load quicly a file in memory to send it to user as http anwser.\n";

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(Common, toString_int)
{
	string str = toString(10);
	SVUT_ASSERT_EQUAL("10",str);
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(Common, toString_float)
{
	string str = toString(10.5);
	SVUT_ASSERT_EQUAL("10.5",str);
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(Common, loadFileInMemory_ok)
{
	size_t size;
	char * buffer = loadFileInMemory(TEST_DATA "/loadFileInMemory.txt",&size);
	char * b = strndup(buffer,size);

	SVUT_ASSERT_EQUAL(TEST_STRING_1.size(),size);
	SVUT_ASSERT_EQUAL(TEST_STRING_1,b);

	free(buffer);
	free(b);
}

/*******************  FUNCTION  *********************/
SVUT_DECLARE_FLAT_TEST(Common, loadFileInMemory_nook)
{
	size_t size;
	char * buffer = loadFileInMemory("/bad_file_path",&size,false);

	SVUT_ASSERT_NULL(buffer);
}

/*******************  FUNCTION  *********************/
SVUT_USE_DEFAULT_MAIN
