/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstring>
#include <cstdio>
#include "TopHttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
LinuxTop::LinuxTop(void )
{
	memset(cpu,0,sizeof(cpu));
	btime = 0;
	proc_running = 0;
	nbCpu = 0;
}

/*******************  FUNCTION  *********************/
void LinuxTop::setNbCpu(int nbCpu)
{
	this->nbCpu = nbCpu;
}

/*******************  FUNCTION  *********************/
LinuxTopCpu::LinuxTopCpu(void )
{
	user = 0;
	nice = 0;
	system = 0;
	idle = 0;
	iowait = 0;
	irq = 0;
	softirq = 0;
}

/*******************  FUNCTION  *********************/
TopHttpNode::TopHttpNode(const std::string& addr)
	:JsonHttpNode<LinuxTop>(addr,&data)
{
	this->readBuffer = new char[HTOPML_TOP_READBUF_SIZE];
}

/*******************  FUNCTION  *********************/
TopHttpNode::~TopHttpNode(void )
{
	if (this->readBuffer != NULL)
		delete[] this->readBuffer;
}

/*******************  FUNCTION  *********************/
void TopHttpNode::onRequest(const HttpRequest & request)
{
	loadGlobalProcStat();
	loadProcessProcStat();
}

/*******************  FUNCTION  *********************/
void TopHttpNode::loadProcessProcStat(void )
{
	FILE * fp = fopen("/proc/self/stat","r");
	if (fp == NULL)
	{
		perror("/proc/self/stat");
		abort();
	} else {
		parseProcessProcStat(data,fp);
		fclose(fp);
	}
}

/*******************  FUNCTION  *********************/
void TopHttpNode::loadGlobalProcStat(void )
{
	FILE * fp = fopen("/proc/stat","r");
	if (fp == NULL)
	{
		perror("/proc/stat");
		abort();
	} else {
		parseGlobalProcStat(data,fp);
		fclose(fp);
	}
}

/*******************  FUNCTION  *********************/
void TopHttpNode::parseProcessProcStat(LinuxTop& top, FILE* fp) const
{
	//vars
	char * tmp;
	size_t size;
	int trash_int;
	unsigned long trash_ulong;
	char trash_char;

	//errors
	assert(fp != NULL);

	//read from file
	size = fread(readBuffer,1,32*4096,fp);
	assert(size > 0);
	assert(size < 32*4096);

	//search end of filename :
	tmp = readBuffer;
	while (*tmp != ')' && tmp != '\0')
		tmp++;
	assert(*tmp == ')');

	//parse
	size = sscanf(tmp+1," %c %d %d %d %d %lu %lu %lu %lu %lu %ld %ld %ld %ld ",
	              &trash_char,&trash_int,&trash_int,&trash_int,&trash_int,
	              &trash_ulong,&trash_ulong,&trash_ulong,&trash_ulong,&trash_ulong,
	              &(top.process_user),&(top.process_system),&(top.process_cum_user),
	              &(top.process_cum_system));
	assert(size == 14);
}

/*******************  FUNCTION  *********************/
void TopHttpNode::parseGlobalProcStat(htopml::LinuxTop& top, FILE* fp) const
{
	//vars
	char * next = readBuffer;
	char * cur = readBuffer;
	int size;

	//errors
	assert(fp != NULL);

	//read from file
	size = fread(readBuffer,1,32*4096,fp);
	if (size >= 32*4096 - 1)
	{
		fprintf(stderr,"Buffer is to small to read /proc/stat in one step.");
		abort();
	} else if (size <= 0) {
		perror("fread");
		abort();
	} else {
		readBuffer[size] = '\0';
	}

	//parse it
	while (cur != NULL)
	{
		next = findEndOfLine(cur);
		if (sscanf(cur,"btime %lu",&top.btime) == 1) {
		} else if (sscanf(cur,"procs_running %lu",&top.proc_running) == 1) {
		} else if (strncmp(cur,"cpu ",4) == 0 || strncmp(cur,"cpu\t",4) == 0 ) {
			parseGlobalProcStatCpuLine(top.total,cur);
		} else if (sscanf(cur,"cpu%d ",&top.nbCpu) == 1) {
			parseGlobalProcStatCpuLine(top.cpu[top.nbCpu],cur);
			top.nbCpu++;
		}
		cur = next;
	}
}

/*******************  FUNCTION  *********************/
void TopHttpNode::parseGlobalProcStatCpuLine(LinuxTopCpu& cpu, const char* value) const
{
	int tmp;
	int cnt;
	if (strncmp(value,"cpu ",4) == 0 || strncmp(value,"cpu\t",4) == 0 )
	{
		cnt = sscanf(value,"cpu %lu %lu %lu %lu %lu %lu %lu",
		            &cpu.user,&cpu.nice,
		            &cpu.system,&cpu.idle,
		            &cpu.iowait,&cpu.irq,
		            &cpu.softirq);
		assert(cnt == 7);
	} else {
		cnt = sscanf(value,"cpu%d %lu %lu %lu %lu %lu %lu %lu",
		            &tmp,&cpu.user,&cpu.nice,
		            &cpu.system,&cpu.idle,
		            &cpu.iowait,&cpu.irq,
		            &cpu.softirq);
		assert(cnt == 8);
	}
}

/*******************  FUNCTION  *********************/
char* TopHttpNode::findEndOfLine(char* start, bool cutWithZero)
{
	assert(start != NULL);
	while (*start != '\0' && *start != '\n')
		start++;
	if (*start == '\0')
	{
		return NULL;
	} else if (*start == '\n') {
		if (cutWithZero)
			*start = '\0';
		return start+1;
	} else {
		abort();
	}
}

/*******************  FUNCTION  *********************/
void convertToJson(JsonState& json, const LinuxTop& value)
{
	json.openStruct();
	json.printFieldArray("cpus",value.cpu,value.nbCpu);
	json.printField("total",value.total);
	json.printField("btime",value.btime);
	json.printField("proc_running",value.proc_running);
	json.printField("nbCpu",value.nbCpu);
	json.printField("process_user",value.process_user);
	json.printField("process_system",value.process_system);
	json.printField("process_cum_user",value.process_cum_user);
	json.printField("process_cum_system",value.process_cum_system);
	json.closeStruct();
}

/*******************  FUNCTION  *********************/
void convertToJson(JsonState& json, const LinuxTopCpu& value)
{
	json.openStruct();
	json.printField("user",value.user);
	json.printField("nice",value.nice);
	json.printField("system",value.system);
	json.printField("idle",value.idle);
	json.printField("iowait",value.iowait);
	json.printField("irq",value.irq);
	json.printField("softirq",value.softirq);
	json.closeStruct();
}

}
