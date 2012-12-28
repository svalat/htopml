/*****************************************************
             PROJECT  : svUnitTest
             VERSION  : 0.5.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef FAKE_SVUT_ASSERT_HEADER
#define FAKE_SVUT_ASSERT_HEADER

/********************  HEADERS  *********************/
#include <string>
#include <sstream>
#include "svutAsserter.h"

/********************  NAMESPACE  *******************/
namespace svUnitTest
{

/*******************  FUNCTION  *********************/
inline std::string getLocationString(int line,const char * filename,const char * function)
{
	std::stringstream res;
	res << "line " << line << " of file " << filename << " on methode " << function << "()";
	return res.str();
}

/********************  MACRO  ***********************/
#define SVUT_NOT_SUPPORTED_MACRO(x) throw svUnitTest::svutExAssertFake("FAILED","Macro not supported : " #x,SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_CODE_LOCATION getLocationString(__LINE__,__FILE__,__FUNCTION__)

/********************  MACROS  **********************/
#define SVUT_CODE_LOCATION_STATIC svUnitTest::getLocationString(__LINE__,__FILE__,"[none]")

/********************  MACRO  ***********************/
#define SVUT_CAPTURE_ASSERT_EXCEPTIONS(x) \
	try{\
		x;\
	} catch (svutExAssertFake & e) {\
		setErrorMessage(e);\
	} catch (...) {\
		svUnitTest::svutExAssertFake e("UNKNOWN","Unknown exception thrown",SVUT_CODE_LOCATION);\
		setErrorMessage(e);\
	}

/********************  MACRO  ***********************/
#define SVUT_ASSERT_TRUE(value) \
	if (((bool)(value)) ==  false) throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #value " == true"),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_FALSE(value) \
	if (((bool)(value)) ==  true) throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #value " == false"),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_NULL(value)\
	if (((void*)(value)) != NULL) \
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #value " == NULL"),SVUT_CODE_LOCATION)


/********************  MACRO  ***********************/
#define SVUT_ASSERT_NOT_NULL(value)\
	if (((void*)(value)) == NULL) \
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #value " != NULL"),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_EQUAL(expected,actual) \
	if (asserterOperatorEqual(expected,actual) == false)\
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " == " #expected),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_NOT_EQUAL(expected,actual) \
	if (asserterOperatorNotEqual(expected,actual) == false)\
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " != " #expected),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_ZERO(value) \
	if (asserterOperatorEqualZero((value)) == false)\
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #value " != 0"),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_ZEROS(value,size) \
	if (asserterOperatorEqualZeros((value),(size)) == false)\
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : each of " #value "[" #size "] != 0"),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_EQUAL_STRICT(expected,actual)\
	if (asserterOperatorEqualStrict(expected,actual) == false)\
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " == " #expected),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_NOT_EQUAL_STRICT(expected,actual)\
	if (asserterOperatorNotEqualStrict(expected,actual) == false)\
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " != " #expected),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_GT(expectedLimit,actual)\
	if (asserterOperatorGT((actual),(expectedLimit)) == false) \
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " >= " #expectedLimit),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_GE(expectedLimit,actual)\
	if (asserterOperatorGE((actual),(expectedLimit)) == false) \
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " >= " #expectedLimit),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_LT(expectedLimit,actual)\
	if (asserterOperatorLT((actual),(expectedLimit)) == false) \
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " >= " #expectedLimit),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_LE(expectedLimit,actual)\
	if (asserterOperatorLE((actual),(expectedLimit)) == false) \
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " >= " #expectedLimit),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_SAME(expected,actual)\
	if ((void*)(expected) != (void*)(actual))\
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " == " #expected),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_NOT_SAME(expected,actual)\
	if ((void*)(expected) == (void*)(actual))\
		throw svUnitTest::svutExAssertFake("FAILED",("Assert fail : " #actual " != " #expected),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_FAIL(message) \
	throw svUnitTest::svutExAssertFake("FAILED",message,SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_TODO(message)\
	throw svUnitTest::svutExAssertFake("TODO",("Todo : " message),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_INDEV(message)\
	throw svUnitTest::svutExAssertFake("INDEV",("Indev : " message),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_NOT_EXEC_THIS()\
	throw svUnitTest::svutExAssertFake("FAILED",("This line must be skiped"),SVUT_CODE_LOCATION)

/********************  MACRO  ***********************/
#define SVUT_ASSERT_THROW(name,what)\
	try {\
		what;\
		throw svUnitTest::svutExAssertFake("FAILED",("Don't get expected " #name " exception"),SVUT_CODE_LOCATION);\
	} catch(name) {\
	}  catch(svUnitTest::svutExAssertFake &) { \
		throw; \
	} catch(...) {\
		throw svUnitTest::svutExAssertFake("UNKNOWN",("Get unknown exception instead of expected " #name " exception"),SVUT_CODE_LOCATION);\
	}

/********************  MACRO  ***********************/
#define SVUT_ASSERT_THROW_SOMETHING(what) \
	try {\
		what;\
		throw svUnitTest::svutExAssertFake("FAILED",("Don't get expected exception"),SVUT_CODE_LOCATION);\
	}  catch(svUnitTest::svutExAssertFake &) { \
		throw; \
	} catch(...) {\
	}

/********************  MACRO  ***********************/
#define SVUT_ASSERT_NOT_THROW(name,what)\
	try {\
		what;\
	} catch(name) {\
		throw svUnitTest::svutExAssertFake("FAILED",("Get unexpected " #name " exception"),SVUT_CODE_LOCATION);\
	} catch(...) {\
	}

/********************  MACRO  ***********************/
#define SVUT_ASSERT_MAY_NOT_THROW(what) \
	try {\
		what;\
	} catch(...) {\
		throw svUnitTest::svutExAssertFake("FAILED",("Get unexpected unknown exception"),SVUT_CODE_LOCATION);\
	}

}

#endif
