/*****************************************************
             PROJECT  : svUnitTest
             VERSION  : 0.5.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef FAKE_SVUT_TEST_CASE_HEADER
#define FAKE_SVUT_TEST_CASE_HEADER

/********************  HEADERS  *********************/
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "svutAssert.h"

/********************  NAMESPACE  *******************/
namespace svUnitTest
{
	
/********************  MACROS  **********************/
#define SVUT_REG_TEST_METHOD(x) markStartTest(#x); SVUT_CAPTURE_ASSERT_EXCEPTIONS(setUp();x();tearDown();); markStatus()
#define SVUT_REGISTER_TEST_CASE(name)\
	static svUnitTest::svutTestCaseBuilderGeneric<name> ___FAKE_SVUNITTEST_case_##name##___;\
	static int ___FAKE_SVUNITTEST_res_case_registration_of##name##__ = svUnitTest::fakeRegisterTestCase(___FAKE_SVUNITTEST_case_##name##___)

/********************  MACROS  **********************/
#define SVUT_SET_CONTEXT(name,value) /*this->setContextEntry((name),(value))*/

/********************  MACROS  **********************/

#define SVUT_UNSET_CONTEXT(name) /*this->clearContexEntry((name))*/

/********************  MACROS  **********************/
#define SVUT_RESET_CONTEXT() /*this->resetContexEntries()*/

/********************  MACROS  **********************/
//printf
#define SVUT_PRINTF 

/********************  MACROS  **********************/
#define SVUT_COUT std::cout

/********************  MACROS  **********************/
#define SVUT_PUTS(x) /* puts((x)) */

/*********************  CLASS  **********************/
/**
 * This is just a light implementation to fake the full library implementation. This may
 * permit to run a test suite bases on svUnitTest in degraded mode even if the library wasn't
 * present. It will directly use assertion so crash on first error and didn't provide any nice
 * output presentation.
**/
class svutTestCase
{
	public:
		inline svutTestCase(std::string name="Undefined");
		inline virtual ~svutTestCase(void);
		inline virtual void setUp(void);
		inline virtual void tearDown(void);
		inline bool runTestCase(void);
		inline std::string getName(void) const;
		inline void setErrorMessage(svutExAssertFake & e);
	protected:
		inline void markStatus(void);
		inline void markStartTest(std::string name);
		inline virtual void testMethodsRegistration(void);
		inline void setTestCaseName(std::string name);
		inline void MARK_AS_KNOWN_ERROR(std::string message);
	private:
		//copy is forbidden
		svutTestCase(const svutTestCase & testCase);
	private:
		std::string caseName;
		svutExAssertFake status;
		bool finalRes;
};

/*********************  CLASS  **********************/
class svutTestCaseBuilder
{
	public:
		inline virtual ~svutTestCaseBuilder(void);
		virtual svutTestCase * build(void) = 0;
};

/********************  GLOBALS  **********************/
extern std::vector<svutTestCaseBuilder *> * __fake_svut_test_cases_registry__;

/*********************  CLASS  **********************/
template <class T>
class svutTestCaseBuilderGeneric : public svutTestCaseBuilder
{
	public:
		inline virtual svutTestCase * build(void) { return new T();}
};

/*******************  FUNCTION  *********************/
inline svutTestCase::svutTestCase(std::string name)
{
	this->caseName = name;
	this->finalRes = false;
}

/*******************  FUNCTION  *********************/
inline svutTestCase::~svutTestCase(void)
{
}

/*******************  FUNCTION  *********************/
inline void svutTestCase::setUp(void)
{
	//nothing to do
}

/*******************  FUNCTION  *********************/
inline void svutTestCase::tearDown(void)
{
	//nothing to do
}

/*******************  FUNCTION  *********************/
inline bool svutTestCase::runTestCase(void)
{
	this->finalRes = true;
	this->testMethodsRegistration();
	return finalRes;
}

/*******************  FUNCTION  *********************/
inline void svutTestCase::markStatus(void)
{
	std::cout << '[' << status.status << ']' << std::endl;
	if (status.status != "SUCCESS" && status.message.empty() == false)
	{
		std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
		std::cout << status.location << std::endl;
		std::cout << status.message << std::endl;
		std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
	}
	if (status.status != "SUCCESS" && status.status != "TODO")
		finalRes = false;
}

/*******************  FUNCTION  *********************/
inline void svutTestCase::markStartTest(std::string name)
{
	std::cout.fill('.');
	std::cout.width(49);
	std::cout << name;
	status.status = "SUCCESS";
}

/*******************  FUNCTION  *********************/
inline void svutTestCase::testMethodsRegistration(void)
{
}

/*******************  FUNCTION  *********************/
inline void svutTestCase::setTestCaseName(std::string name)
{
	this->caseName = name;
}

/*******************  FUNCTION  *********************/
inline void svutTestCase::MARK_AS_KNOWN_ERROR(std::string message)
{
}

/*******************  FUNCTION  *********************/
inline void svutTestCase::setErrorMessage(svutExAssertFake & e)
{
	this->status = e;
}

/*******************  FUNCTION  *********************/
inline std::string svutTestCase::getName(void) const
{
	return caseName;
}

/*******************  FUNCTION  *********************/
inline svutTestCaseBuilder::~svutTestCaseBuilder(void)
{
}

/*******************  FUNCTION  *********************/
static inline int fakeRegisterTestCase(svUnitTest::svutTestCaseBuilder & builder)
{
	if (__fake_svut_test_cases_registry__ == NULL)
		__fake_svut_test_cases_registry__ = new std::vector<svutTestCaseBuilder *>;
	svUnitTest::__fake_svut_test_cases_registry__->push_back(&builder);
	return 0;
}

}

#endif
