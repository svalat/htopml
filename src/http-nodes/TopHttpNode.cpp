/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
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
}

/*******************  FUNCTION  *********************/
void TopHttpNode::onRequest(const HttpRequest & request)
{
	FILE * fp = fopen("/proc/stat","r");
	if (fp == NULL)
	{
		perror("/proc/stat");
		abort();
	} else {
		parseProcStat(data,fp);
		fclose(fp);
	}
}

/*******************  FUNCTION  *********************/
void TopHttpNode::parseProcStat(htopml::LinuxTop& top, FILE* fp) const
{
	//vars
	char buffer[4096];
	char * next = buffer;
	char * cur = buffer;
	int size;

	//errors
	assert(fp != NULL);

	//read from file
	size = fread(buffer,1,sizeof(buffer),fp);
	if (size == sizeof(buffer))
	{
		fprintf(stderr,"Buffer is to small to read /proc/stat in one step.");
		abort();
	} else if (size <= 0) {
		perror("fread");
		abort();
	}

	//parse it
	while (cur != NULL)
	{
		next = findEndOfLine(cur);
		if (sscanf(cur,"btime %lu",&top.btime) == 1) {
		} else if (sscanf(cur,"procs_running %lu",&top.proc_running) == 1) {
		} else if (strncmp(cur,"cpu ",4) == 0 || strncmp(cur,"cpu\t",4) == 0 ) {
			parseProcStatCpuLine(top.total,cur);
		} else if (sscanf(cur,"cpu%d ",&top.nbCpu) == 1) {
			parseProcStatCpuLine(top.cpu[top.nbCpu],cur);
			top.nbCpu++;
		}
		cur = next;
	}
}

/*******************  FUNCTION  *********************/
void TopHttpNode::parseProcStatCpuLine(LinuxTopCpu& cpu, const char* value) const
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
void typeToJson(JsonState& json, std::ostream& stream, const LinuxTop& value)
{
	json.openStruct();
	json.printFieldArray("cpus",value.cpu,value.nbCpu);
	json.printField("total",value.total);
	json.printField("btime",value.btime);
	json.printField("proc_running",value.proc_running);
	json.printField("nbCpu",value.nbCpu);
	json.closeStruct();
}

/*******************  FUNCTION  *********************/
void typeToJson(JsonState& json, std::ostream& stream, const LinuxTopCpu& value)
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

};
