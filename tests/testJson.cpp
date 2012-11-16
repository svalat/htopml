/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <sstream>
#include <gtest/gtest.h>
#include "../src/json/TypeToJson.h"

/**********************  USING  *********************/
using namespace std;
using namespace htopml;

/*********************  CONSTS  *********************/
static const char * TEST_STRING_1 = "\"coucou\"";
static const char * TEST_STRING_2 = "25";
static const char * TEST_STRING_3 = "25.3";
static const char * TEST_STRING_4 = "\"coucou \\\" guillimet\"";
static const char * TEST_STRING_5 = "{\n\
\t\"a\": 10,\n\
\t\"b\": 25.3,\n\
\t\"c\": [ 1, 2, 3, 4],\n\
\t\"d\": true,\n\
\t\"e\": false\n\
}";

/*********************  STRUCT  *********************/
struct TestStruct1
{
	int a;
	double b;
	long c[4];
	bool d;
	bool e;
};

/*******************  FUNCTION  *********************/
void typeToJson(JsonState & json,std::ostream& stream, const TestStruct1 & value)
{
	json.openStruct();
	json.printField("a",value.a);
	json.printField("b",value.b);
	json.printFieldArray("c",value.c,4);
	json.printField("d",value.d);
	json.printField("e",value.e);
	json.closeStruct();
}

/*******************  FUNCTION  *********************/
TEST(TypeToJson, basicString)
{
	string value = "coucou";
	stringstream str;
	typeToJson(str,value);
	EXPECT_EQ(TEST_STRING_1,str.str());
}

/*******************  FUNCTION  *********************/
TEST(TypeToJson, basicStringEscape)
{
	string value = "coucou \" guillimet";
	stringstream str;
	typeToJson(str,value);
	EXPECT_EQ(TEST_STRING_4,str.str());
}

/*******************  FUNCTION  *********************/
TEST(TypeToJson, basicInt)
{
	stringstream str;
	typeToJson(str,25);
	EXPECT_EQ(TEST_STRING_2,str.str());
}

/*******************  FUNCTION  *********************/
TEST(TypeToJson, basicFloat)
{
	stringstream str;
	typeToJson(str,25.3);
	EXPECT_EQ(TEST_STRING_3,str.str());
}

/*******************  FUNCTION  *********************/
TEST(TypeToJson, basicStruct1)
{
	stringstream str;
	TestStruct1 obj = {10,25.3,{1,2,3,4},true,false};
	typeToJson(str,obj);
	EXPECT_EQ(TEST_STRING_5,str.str());
}

/*******************  FUNCTION  *********************/
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
