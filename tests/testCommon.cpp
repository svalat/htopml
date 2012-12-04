/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <string>
#include <gtest/gtest.h>
#include "Common.h"

/**********************  USING  *********************/
using namespace std;
using namespace htopml;

/*********************  CONSTS  *********************/
static const char TEST_STRING_1[] = "This is a test to load quicly a file in memory to send it to user as http anwser.\n";

/*******************  FUNCTION  *********************/
TEST(Common, toString_int)
{
	string str = toString(10);
	EXPECT_EQ("10",str);
}

/*******************  FUNCTION  *********************/
TEST(Common, toString_float)
{
	string str = toString(10.5);
	EXPECT_EQ("10.5",str);
}

/*******************  FUNCTION  *********************/
TEST(Common, loadFileInMemory_ok)
{
	size_t size;
	char * buffer = loadFileInMemory(TEST_DATA "/loadFileInMemory.txt",&size);
	char * b = strndup(buffer,size);

	EXPECT_EQ(sizeof(TEST_STRING_1)-1,size);
	EXPECT_STREQ(TEST_STRING_1,b);

	free(buffer);
	free(b);
}

/*******************  FUNCTION  *********************/
TEST(Common, loadFileInMemory_nook)
{
	size_t size;
	char * buffer = loadFileInMemory("/bad_file_path",&size,false);

	EXPECT_EQ(NULL,buffer);
}

/*******************  FUNCTION  *********************/
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
