/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_TOP_WEB_NODE_H
#define HTOPML_TOP_H

/********************  HEADERS  *********************/
#include "../server/JsonWebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/********************  MACRO  ***********************/
#define HTOPML_TOP_MAX_CPU 128

/*********************  STRUCT  *********************/
class LinuxTopCpu
{
	public:
		LinuxTopCpu(void);
		void setAsDelta(const LinuxTopCpu & previous,const LinuxTopCpu & current);
	public:
		unsigned long user;
		unsigned long nice;
		unsigned long system;
		unsigned long idle;
		unsigned long iowait;
		unsigned long irq;
		unsigned long softirq;
};

/*********************  STRUCT  *********************/
class LinuxTop
{
	public:
		LinuxTop(void);
		void setAsDelta(const LinuxTop & previous,const LinuxTop & current);
		void setNbCpu(int nbCpu);
	public:
		struct LinuxTopCpu cpu[HTOPML_TOP_MAX_CPU];
		unsigned long btime;
		unsigned long proc_running;
		int nbCpu;
};

/*********************  CLASS  **********************/
class TopWebNode : public JsonWebNode<LinuxTop>
{
	public:
		TopWebNode(const std::string & addr);
		virtual void onRequest(const mg_request_info* request_info);
	private:
		void parseProcStat(LinuxTop & top,FILE * fp);
		static char * findEndOfLine(char * start,bool cutWithZero = true);
	private:
		LinuxTop delta;
		LinuxTop last;
};

/*******************  FUNCTION  *********************/
void typeToJson(JsonState & json,std::ostream& stream, const LinuxTop & value);
void typeToJson(JsonState & json,std::ostream& stream, const LinuxTopCpu & value);

};

#endif // HTOPML_LINUX_GET_RUSAGE_WEB_NODE_H
