/*****************************************************
             PROJECT  : svUnitTest
             VERSION  : 0.5.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef FAKE_SVUT_ASSERTER_HEADER
#define FAKE_SVUT_ASSERTER_HEADER

/********************  HEADERS  *********************/
#include <sstream>
#include <cstring>
#include "svutExAssert.h"

/********************  NAMESPACE  *******************/
namespace svUnitTest
{

/*******************  FUNCTION  *********************/
template <class T1,class T2>
bool asserterOperatorEqual(const T1 & v1,const T2 & v2)
{
	return (v1 == v2);
}

/*******************  FUNCTION  *********************/
template <class T1,class T2>
bool asserterOperatorNotEqual(const T1 & v1,const T2 & v2)
{
	return (v1 != v2);
}

/*******************  FUNCTION  *********************/
template <class T1,class T2>
static bool asserterOperatorGT(const T1 & v1,const T2 & v2)
{
	return (v1 > v2);
}

/*******************  FUNCTION  *********************/
template <class T1,class T2>
static bool asserterOperatorGE(const T1 & v1,const T2 & v2)
{
	return (v1 >= v2);
}

/*******************  FUNCTION  *********************/
template <class T1,class T2>
static bool asserterOperatorLT(const T1 & v1,const T2 & v2)
{
	return (v1 < v2);
}

/*******************  FUNCTION  *********************/
template <class T1,class T2>
static bool asserterOperatorLE(const T1 & v1,const T2 & v2)
{
	return (v1 <= v2);
}

/*******************  FUNCTION  *********************/
template <class T>
std::string asserterToString(const T & value)
{
	std::stringstream res;
	res << value;
	return res.str();
}

/*******************  FUNCTION  *********************/
template <class T>
bool asserterOperatorEqualStrict(const T & expected,const T & actual)
{
	return asserterOperatorEqual(expected,actual);
}

/*******************  FUNCTION  *********************/
template <class T>
bool asserterOperatorNotEqualStrict(const T & expected,const T & actual)
{
	return asserterOperatorNotEqual(expected,actual);
}

/*******************  FUNCTION  *********************/
template <class T>
static bool asserterOperatorEqualZero(const T & value)
{
	return (value == (T)0);
}

/*******************  FUNCTION  *********************/
template <class T>
static bool asserterOperatorEqualZeros(const T * value,size_t size)
{
	for (size_t i = 0 ; i < size ; ++i)
		if (asserterOperatorEqualZero(value[i]) == false)
			return false;
	return true;
}

/*******************  FUNCTION  *********************/
// template <class T>
// static void assertNotEqualStrict(const T & expected,const T & actual,svutCodeLocation location) throw(svutExAssertFailEqual)
// {
// 	assertNotEqual(expected,actual,location);
// }

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorEqual(const char * expected,const char * actual)
{
	return strcmp(expected,actual) == 0;
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorNotEqual(const char * expected,const char * actual)
{
	return strcmp(expected,actual) != 0;
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorEqualStrict(const char * expected,const char * actual)
{
	return asserterOperatorEqual(expected,actual);
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorNotEqualStrict(const char * expected,const char * actual)
{
	return asserterOperatorNotEqual(expected,actual);
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorGE(const char * v1,const char * v2)
{
	return v1 >= v2;
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorGT(const char * v1,const char * v2)
{
	return v1 > v2;
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorLE(const char * v1,const char * v2)
{
	return v1 <= v2;
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorLT(const char * v1,const char * v2)
{
	return v1 < v2;
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorGE(char * v1,char * v2)
{
	return v1 >= v2;
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorGT(char * v1,char * v2)
{
	return v1 > v2;
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorLE(char * v1,char * v2)
{
	return v1 <= v2;
}

/*******************  FUNCTION  *********************/
static inline bool asserterOperatorLT(char * v1,char * v2)
{
	return v1 < v2;
}

}

#endif
