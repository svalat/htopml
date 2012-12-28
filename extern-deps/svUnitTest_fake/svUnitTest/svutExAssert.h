/*****************************************************
             PROJECT  : svUnitTest
             VERSION  : 0.5.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef SVUT_EX_ASSERT_HEADER
#define SVUT_EX_ASSERT_HEADER

/********************  HEADERS  *********************/
#include <string>

/********************  NAMESPACE  *******************/
namespace svUnitTest
{

/********************  MACROS  **********************/
#define SVUT_STATUS_TODO "TODO"
#define SVUT_STATUS_INDEV "INDEV"
#define SVUT_STATUS_SKIPED "SKIPED"
#define SVUT_STATUS_SUCCESS "SUCCESS"
#define SVUT_STATUS_FAILED "FAILED"
#define SVUT_STATUS_UNKNOWN "UNKNOWN"

/********************** TYPEDEF *********************/
typedef std::string svutCodeLocation;
typedef std::string svutStatus;

/*********************  CLASS  **********************/
class svutExAssertFake
{
	public:
		svutExAssertFake(svutStatus status,std::string message,svutCodeLocation location)  throw()
		{
			this->status = status;
			this->message = message;
			this->location = location;
		}
		svutExAssertFake(void) {}
		svutStatus status;
		std::string message;
		svutCodeLocation location;
};

/*********************  CLASS  **********************/
class svutExTestStatus : public svutExAssertFake
{
	public:
		svutExTestStatus(void) {}
		svutExTestStatus(std::string name,svutStatus status,svutCodeLocation  location,std::string message="")  throw()
		{
			this->location = location;
			this->message = message;
		}
};

/*********************  CLASS  **********************/
class svutExAssertFail : public svutExTestStatus
{
	public:
		svutExAssertFail(std::string name, svutStatus status, const svutCodeLocation & location, std::string message) throw()
			: svutExTestStatus("AssertFail:"+name, status, location, message)
		{
		}
};

/*********************  CLASS  **********************/
class svutExAssertFailBool : public svutExAssertFail
{
	public:
		svutExAssertFailBool(bool expected, const svutCodeLocation &  location) throw()
			: svutExAssertFail("AssertBool",SVUT_STATUS_FAILED,location,"Failed on BOOLEAN test.")
		{
		}
};

/*********************  CLASS  **********************/
class svutExAssertFailNullPointer : public svutExAssertFail
{
	public:
		svutExAssertFailNullPointer(bool expectNull, svutCodeLocation  location) throw()
			: svutExAssertFail("AssertNull",SVUT_STATUS_FAILED,location,"Failed on NULL pointer test.")
		{
			
		}
};

/*********************  CLASS  **********************/
class svutExAssertFailEqual : public svutExAssertFail
{
	public:
		svutExAssertFailEqual(bool expectTestRes,std::string exptected,std::string actual,
			svutCodeLocation  location) throw()
			: svutExAssertFail("AssertEqual",SVUT_STATUS_FAILED,location,"Failed on expected value.")
		{
		}
};

/*********************  CLASS  **********************/
class svutExAssertFailCustom : public svutExAssertFail
{
	public:
		svutExAssertFailCustom(std::string message, svUnitTest::svutCodeLocation location) throw()
			: svutExAssertFail("AssertCustom",SVUT_STATUS_FAILED,location,message)
		{
		}
};

/*********************  CLASS  **********************/
class svutExAssertFailNotExec : public svutExAssertFail
{
	public:
		svutExAssertFailNotExec(svutCodeLocation  location) throw()
			:svutExAssertFail("AssertNotExec",SVUT_STATUS_FAILED,location,"Failed on execution of forbidden bloc.")
		{
			
		}
};

/*********************  CLASS  **********************/
class svutExAssertFailThrow : public svutExAssertFail
{
	public:
		svutExAssertFailThrow(std::string expected,std::string actual,
			svutCodeLocation  location) throw()
			: svutExAssertFail("AssertThrow",SVUT_STATUS_FAILED,location,"Failed on waiting exception.")
		{
			
		}
};

}

#endif
