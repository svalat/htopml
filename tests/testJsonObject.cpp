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
#include "../src/json/JsonObject.h"

/**********************  USING  *********************/
using namespace std;
using namespace htopml;

/*********************  CONSTS  *********************/
static const char * TEST_STRING_1 = "{\n\t\"a\": 10,\n\t\"b\": 3.2,\n\t\"c\": 5,\n\t\"d\": 1.3\n}";
static const char * TEST_STRING_2 = "{\n\t\"a\": 10,\n\t\"b\": 3.2,\n\t\"c\": 5,\n\t\"d\": 1.3\n}\n{\n\t\"a\": 10,\n\t\"b\": 3.2,\n\t\"c\": 20,\n\t\"d\": 9\n}";

/*********************  STRUCT  *********************/
class TestClass1 : public JsonObject
{
	public:
		TestClass1(void);
		int a;
		double b;
		int c;
		double d;
};

/*******************  FUNCTION  *********************/
TestClass1::TestClass1(void )
{
	this->a = 10;
	this->b = 3.2;
	this->c = 5;
	this->d = 1.3;
	registerField("a",&a);
	registerField("b",&b);
	registerDeltaField("c",&c);
	registerDeltaField("d",&d);
}

/*******************  FUNCTION  *********************/
TEST(JsonObject, basicConversion)
{
	TestClass1 t;
	stringstream str;
	typeToJson(str,t);
	EXPECT_EQ(TEST_STRING_1,str.str());
}

/*******************  FUNCTION  *********************/
TEST(JsonObject, deltaComputation)
{
	TestClass1 t;
	stringstream str;
	typeToJson(str,t);
	str << "\n";
	t.c = 25;
	t.d = 10.3;
	typeToJson(str,t);
	EXPECT_EQ(TEST_STRING_2,str.str());
}

/*******************  FUNCTION  *********************/
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
