/*****************************************************
             PROJECT  : svUnitTest
             VERSION  : 0.5.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef SVUT_FLAT_TEST_CASE_HEADER
#define SVUT_FLAT_TEST_CASE_HEADER

/********************  HEADERS  *********************/
#include "svutTestCase.h"
#include <vector>
#include <set>
#include <map>

/********************  NAMESPACE  *******************/
namespace svUnitTest
{

/********************  MACROS  **********************/
/**
 * Convert the given name to string.
 * @param value Define the value to convert to string.
 * @version 0.4.0
**/
#define SVUT_DECLARE_FLAT_TEST_STR(value) #value

/********************  MACROS  **********************/
/**
 * Register a flat test function.
 * @param testCaseName Define the name of virtual test case on which to link the flat test.
 * @param testName Define the name of your test (the name of function to declare).
 * @version 0.4.0
**/
#define SVUT_REGISTER_FLAT_TEST_INTERNAL(testCaseName,testName,method) \
	static bool ___SVUT_res_flat_case_method_registration_of_##testCaseName##_##testName##__ = \
		svUnitTest::registerFlatTestCaseMethod(SVUT_DECLARE_FLAT_TEST_STR(testCaseName),\
			SVUT_DECLARE_FLAT_TEST_STR(testName),method,SVUT_CODE_LOCATION_STATIC); \

/********************  MACROS  **********************/
/**
 * Register a flat test function.
 * @param testCaseName Define the name of virtual test case on which to link the flat test.
 * @param testName Define the name of your test (the name of function to declare).
 * @version 0.4.0
**/
#define SVUT_REGISTER_FLAT_TEST(testCaseName,testName) SVUT_REGISTER_FLAT_TEST_INTERNAL(testCaseName,testName,testName)

/********************  MACROS  **********************/
/**SVUNITTEST_INCLUDE_DIRS
 * Declare a flat test function. It will declare a function of type "void name(void)", so place the test
 * body directly after this line. It will automatically declare it and call SVUT_REGISTER_FLAT_TEST
 * @param testCaseName Define the name of virtual test case on which to link the flat test.
 * @param testName Define the name of your test (the name of function to declare).
 * @version 0.4.0
**/
#define SVUT_DECLARE_FLAT_TEST(testCaseName,testName) \
	void testCaseName##_##testName(void);\
	SVUT_REGISTER_FLAT_TEST_INTERNAL(testCaseName,testName,testCaseName##_##testName);\
	void testCaseName##_##testName(void)

/********************  MACROS  **********************/
/**
 * Same than SVUT_REGISTER_FLAT_TEST, but to register the special setUp() function.
**/
#define SVUT_REGISTER_FLAT_SETUP(testCaseName,fctName) \
	SVUT_REGISTER_FLAT_TEST_INTERNAL(testCaseName,__SVUT_SPECIAL_TEST_CASE_SETUP__,fctName)

/********************  MACROS  **********************/
/**
 * Same than SVUT_DECLARE_FLAT_TEST, but to declare the special setUp() function.
**/
#define SVUT_DECLARE_FLAT_SETUP(testCaseName) \
	void testCaseName##_##setUp(void);\
	SVUT_REGISTER_FLAT_TEST_INTERNAL(testCaseName,__SVUT_SPECIAL_TEST_CASE_SETUP__,testCaseName##_##setUp);\
	void testCaseName##_##setUp(void)

/********************  MACROS  **********************/
/**
 * Same than SVUT_REGISTER_FLAT_TEST, but to register the special tearDown() function.
**/
#define SVUT_REGISTER_FLAT_TEAR_DOWN(testCaseName,fctName) \
	SVUT_REGISTER_FLAT_TEST_INTERNAL(testCaseName,__SVUT_SPECIAL_TEST_CASE_TEAR_DOWN__,fctName)

/********************  MACROS  **********************/
/**
 * Same than SVUT_DECLARE_FLAT_TEST, but to declare the special tearDown() function.
**/
#define SVUT_DECLARE_FLAT_TEAR_DOWN(testCaseName) \
	void testCaseName##_##tearDown(void);\
	SVUT_REGISTER_FLAT_TEST_INTERNAL(testCaseName,__SVUT_SPECIAL_TEST_CASE_TEAR_DOWN__,testCaseName##_##tearDown);\
	void testCaseName##_##tearDown(void)

/********************  TYPEDEF  *********************/
/**
 * Define the prototype of methodes for flat test mode (simple C functions).
 * @version 0.4.0
**/
typedef void (*svutTestMethodPtr)(void);

/*********************  STRUCT  *********************/
/**
 * Struct to define registry entry introduced by registerFlatTestCaseMethod() method.
 * @brief Simple structure of stage for flat test case global registry.
 * @version 0.4.0
**/
struct svutFlatRegistryEntry
{
	std::string testCaseName;
	std::string testName;
	svutCodeLocation location;
	svutTestMethodPtr methodPtr;
};

/*********************  CLASS  **********************/
/**
 * Builder to manage the creation of flat test cases by svutRunner if autoloading classes is enabled.
 * @brief Builder for flat test case.
 * @author Valat Sébastien
 * @version 0.4.0
**/
class svutFlatTestCaseBuilder : public svutTestCaseBuilder
{
	public:
	    inline svutFlatTestCaseBuilder(std::string testCaseName);
	    inline virtual svUnitTest::svutTestCase* build(void );
	protected:
		/** Name of flat test case to construct. **/
		std::string testCaseName;
};

/*********************  CLASS  **********************/
/**
 * Special test case used to automatically construct object test case from flat C functions.
 * @brief Test case made of static C functions.
 * @author Valat Sébastien
 * @version 0.4.0
**/
class svutFlatTestCase : public svutTestCase
{
	public:
	    inline svutFlatTestCase(std::string name = "Undefined");
	    inline virtual void testMethodsRegistration(void );
		inline void registerFlatTestMethod(std::string name,svutTestMethodPtr methodPtr,const svutCodeLocation & location);
	protected:
		inline virtual void setUp(void );
		inline virtual void tearDown(void );
	private:
		svutTestMethodPtr setUpPtr;
		svutTestMethodPtr tearDownPtr;
		std::vector<svutFlatRegistryEntry> tests;
};

/*******************  FUNCTION  *********************/
static bool registerFlatTestCaseMethod(const char* testCaseName, const char* functionName, svUnitTest::svutTestMethodPtr methodPtr, const svUnitTest::svutCodeLocation& location);
static std::set<class svutTestCaseBuilder *> getRegistredFlatTestCases(void);

/********************* GLOBALS **********************/
extern std::vector<svutFlatRegistryEntry> * __fake_svut_test_flat_test_registry__;

/*******************  FUNCTION  *********************/
/**
 * Function used to register a new methe by link time trick.
 * @param testCaseName Define the name of test case to create.
 * @param functionName Define the name of the function to use as test case.
 * @param methodPtr Define the pointer of C method to call.
 * @param location Define the location of the method.
 * @return Return always true, this is the trick to call the method at init time without depending
 * on compilers/linker keywords, see SVUT_REGISTER_FLAT_TEST macro.
**/
static inline bool registerFlatTestCaseMethod(const char* testCaseName, const char* functionName, svutTestMethodPtr methodPtr,const svutCodeLocation & location)
{
	if (svUnitTest::__fake_svut_test_flat_test_registry__ == NULL)
		svUnitTest::__fake_svut_test_flat_test_registry__ = new std::vector<svutFlatRegistryEntry>;
	svutFlatRegistryEntry entry;
	entry.testCaseName = testCaseName;
	entry.testName = functionName;
	entry.methodPtr = methodPtr;
	entry.location = location;
	svUnitTest::__fake_svut_test_flat_test_registry__->push_back(entry);
	return true;
}

/*******************  FUNCTION  *********************/
/**
 * Constructor of flat test case.
 * @param name Simply define the name of the flat test case. This name will be used by
 * testMethodsRegistration() to find the related tests.
**/
inline svutFlatTestCase::svutFlatTestCase(std::string name)
	: svutTestCase(name)
{
	setUpPtr = NULL;
	tearDownPtr = NULL;
}

/*******************  FUNCTION  *********************/
/**
 * Register a new test method to the current flat test case.
 * @param name Define the name of the test.
 * @param methodPtr Define the test function to use.
 * @param location Define the location of the function in source code.
**/
inline void svutFlatTestCase::registerFlatTestMethod(std::string name, svutTestMethodPtr methodPtr, const svUnitTest::svutCodeLocation& location)
{
	if (name == "__SVUT_SPECIAL_TEST_CASE_SETUP__")
	{
		this->setUpPtr = methodPtr;
	} else if (name == "__SVUT_SPECIAL_TEST_CASE_TEAR_DOWN__") {
		this->tearDownPtr = methodPtr;
	} else {
		svutFlatRegistryEntry entry;
		entry.location = location;
		entry.methodPtr = methodPtr;
		entry.testCaseName = this->getName();
		entry.testName = name;
		tests.push_back(entry);
	}
}

/*******************  FUNCTION  *********************/
/**
 * Search all corresponding tests by checking testCaseName and create entries in current test case.
**/
inline void svutFlatTestCase::testMethodsRegistration(void )
{
	if (svUnitTest::__fake_svut_test_flat_test_registry__ != NULL)
		for (std::vector<svutFlatRegistryEntry>::const_iterator it = svUnitTest::__fake_svut_test_flat_test_registry__->begin() ; it != svUnitTest::__fake_svut_test_flat_test_registry__->end() ; ++it)
			if (it->testCaseName == getName())
				this->registerFlatTestMethod(it->testName,it->methodPtr,it->location);

	//run all
	for (std::vector<svutFlatRegistryEntry>::iterator it = tests.begin() ; it != tests.end() ; ++it)
	{
		markStartTest(it->testName);
		SVUT_CAPTURE_ASSERT_EXCEPTIONS(setUp();it->methodPtr();tearDown(););
		markStatus();
	}
}

/*******************  FUNCTION  *********************/
/**
 * Call related tearDown method.
**/
inline void svutFlatTestCase::tearDown(void )
{
	if (tearDownPtr != NULL)
		tearDownPtr();
}

/*******************  FUNCTION  *********************/
/**
 * Call related setup method.
**/
inline void svutFlatTestCase::setUp(void )
{
	if (setUpPtr != NULL)
		setUpPtr();
}

/*******************  FUNCTION  *********************/
/**
 * Return the list of test case builder corresponding to all flat test case registred by
 * SVUT_REGISTER_FLAT_TEST macro.
**/
inline static std::set< svutTestCaseBuilder* > getRegistredFlatTestCases(void )
{
	std::set< svutTestCaseBuilder* > res;
	std::map<std::string,bool> filter;

	if (svUnitTest::__fake_svut_test_flat_test_registry__ != NULL)
	{
		for (std::vector<svutFlatRegistryEntry>::const_iterator it = svUnitTest::__fake_svut_test_flat_test_registry__->begin() ; it != svUnitTest::__fake_svut_test_flat_test_registry__->end() ; ++it)
		{
			if (filter.find(it->testCaseName) == filter.end())
			{
				filter[it->testCaseName] = true;
				res.insert(new svutFlatTestCaseBuilder(it->testCaseName));
			}
		}
	}

	return res;
}

/*******************  FUNCTION  *********************/
inline svutFlatTestCaseBuilder::svutFlatTestCaseBuilder(std::string testCaseName)
{
	this->testCaseName = testCaseName;
}

/*******************  FUNCTION  *********************/
inline svutTestCase* svutFlatTestCaseBuilder::build(void )
{
	return new svutFlatTestCase(testCaseName);
}

}

#endif // SVUTFLATTESTCASE_H
