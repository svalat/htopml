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
#include "JsonHttpNode.h"

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
		void setNbCpu(int nbCpu);
	public:
		LinuxTopCpu cpu[HTOPML_TOP_MAX_CPU];
		LinuxTopCpu total;
		unsigned long btime;
		unsigned long proc_running;
		int nbCpu;
		long process_user;
		long process_system;
		long process_cum_user;
		long process_cum_system;
};

/*********************  CLASS  **********************/
class TopHttpNode : public JsonHttpNode<LinuxTop>
{
	public:
		TopHttpNode(const std::string & addr);
		virtual void onRequest(const HttpRequest & request);
	private:
		void loadProcessProcStat(void);
		void parseProcessProcStat(LinuxTop & top,FILE * fp) const;
		void loadGlobalProcStat(void);
		void parseGlobalProcStat(LinuxTop & top,FILE * fp) const;
		void parseGlobalProcStatCpuLine(LinuxTopCpu & cpu,const char * value) const;
		static char * findEndOfLine(char * start,bool cutWithZero = true);
	private:
		LinuxTop data;
};

/*******************  FUNCTION  *********************/
void typeToJson(JsonState & json,std::ostream& stream, const LinuxTop & value);
void typeToJson(JsonState & json,std::ostream& stream, const LinuxTopCpu & value);

}

#endif // HTOPML_LINUX_GET_RUSAGE_WEB_NODE_H
