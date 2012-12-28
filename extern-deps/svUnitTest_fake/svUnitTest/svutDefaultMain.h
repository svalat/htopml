/*****************************************************
             PROJECT  : svUnitTest
             VERSION  : 0.5.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef SVUT_DEFAULT_MAIN_HEADER
#define SVUT_DEFAULT_MAIN_HEADER

/********************  HEADERS  *********************/
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ios>
#include "svutTestCase.h"
#include "svutFlatTestCase.h"

namespace svUnitTest
{

/********************  MACRO  ***********************/
/** Define all global variables (must be called one time only). **/
#define SVUT_FAKE_DECLARE_GLOBAL_VARS\
	std::vector<svutTestCaseBuilder *> * svUnitTest::__fake_svut_test_cases_registry__ = NULL;\
	std::vector<svutFlatRegistryEntry> * svUnitTest::__fake_svut_test_flat_test_registry__ = NULL;

/********************  MACROS  **********************/
#define SVUT_REGISTER_STANDALONE(className) \
	SVUT_FAKE_DECLARE_GLOBAL_VARS\
	int main(int argc,char * argv[]) { \
		svUnitTest::svutTestCaseBuilderGeneric<className> builder;\
		return uniqueStandeloneMain(argc,argv,builder);\
	}

/********************  MACROS  **********************/
/** 
 * Remove this in nexte version (> 0.4.0)
 * @deprecated
**/
#define SVUT_REGISTER_STANDELONE(className) SVUT_REGISTER_STANDALONE(className)

/********************  MACROS  **********************/
#define SVUT_USE_DEFAULT_MAIN \
	SVUT_FAKE_DECLARE_GLOBAL_VARS\
	int main(int argc,char * argv[]) { \
		return defaultMain(argc,argv); \
	}
	
/********************  GLOBALS  **********************/
extern std::vector<svutTestCaseBuilder *> * __fake_svut_test_cases_registry__;

/*******************  FUNCTION  *********************/
static int defaultMain(int argc,char * argv[])
{
	bool final = true;

	std::set<svUnitTest::svutTestCaseBuilder *> lst = getRegistredFlatTestCases();
	if (__fake_svut_test_cases_registry__ != NULL)
		lst.insert(svUnitTest::__fake_svut_test_cases_registry__->begin(),svUnitTest::__fake_svut_test_cases_registry__->end());
	
	for (std::set<svutTestCaseBuilder *>::iterator it = lst.begin(); it != lst.end() ; ++it)
	{
		svutTestCase * test = (*it)->build();
		std::cout << "--------------";
		std::cout.width(30);
		std::cout.setf(std::ios::left);
		std::cout.fill('-');
		std::cout << test->getName();
		std::cout << "-------------- " << std::endl;
		if (test->runTestCase() == false)
			final = false;
		delete test;
	}

	if (__fake_svut_test_cases_registry__ != NULL)
		delete __fake_svut_test_cases_registry__;

	if (__fake_svut_test_flat_test_registry__ != NULL)
		delete __fake_svut_test_flat_test_registry__;

	if (final)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

/*******************  FUNCTION  *********************/
static inline int uniqueStandeloneMain(int argc,char * argv[],svutTestCaseBuilder & builder)
{
	if (__fake_svut_test_cases_registry__ == NULL)
		__fake_svut_test_cases_registry__ = new std::vector<svutTestCaseBuilder *>;
	svUnitTest::__fake_svut_test_cases_registry__->push_back(&builder);
	return defaultMain(argc,argv);
}

}

#endif //SVUT_DEFAULT_MAIN_HEADER
