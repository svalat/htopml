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
#include "TopWebNode.h"

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
void LinuxTop::setAsDelta(const LinuxTop& previous, const LinuxTop& current)
{
	//errors
	assert(previous.nbCpu == current.nbCpu);
	nbCpu = previous.nbCpu;

	//delata of cpu values
	for (int i = 0 ; i < nbCpu ; i++)
		cpu[i].setAsDelta(previous.cpu[i],current.cpu[i]);

	//the other one didn't need delta
	btime = current.btime;
	proc_running = current.proc_running;
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
void LinuxTopCpu::setAsDelta(const LinuxTopCpu& previous, const LinuxTopCpu& current)
{
	user = current.user - previous.user;
	nice = current.nice - previous.nice;
	system = current.system - previous.system;
	idle = current.idle - previous.idle;
	iowait = current.iowait - previous.iowait;
	irq = current.irq - previous.irq;
	softirq = current.softirq - previous.softirq;
}

/*******************  FUNCTION  *********************/
TopWebNode::TopWebNode(const std::string& addr)
	:JsonWebNode<LinuxTop>(addr,&delta)
{
}

/*******************  FUNCTION  *********************/
void TopWebNode::onRequest(const mg_request_info* request_info)
{
	FILE * fp = fopen("/proc/stat","r");
	if (fp == NULL)
	{
		perror("/proc/stat");
		abort();
	} else {
		LinuxTop current;
		parseProcStat(current,fp);
		fclose(fp);
		if (last.nbCpu != 0)
			delta.setAsDelta(last,current);
		last = current;
	}
}

/*******************  FUNCTION  *********************/
void TopWebNode::parseProcStat(LinuxTop& top, FILE* fp)
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
		} else if (sscanf(cur,"cpu%d ",&top.nbCpu) == 1) {
			int tmp;
			int cnt = sscanf(cur,"cpu%d %lu %lu %lu %lu %lu %lu %lu",
				   &tmp,&top.cpu[top.nbCpu].user,&top.cpu[top.nbCpu].nice,
			       &top.cpu[top.nbCpu].system,&top.cpu[top.nbCpu].idle,
			       &top.cpu[top.nbCpu].iowait,&top.cpu[top.nbCpu].irq,
			       &top.cpu[top.nbCpu].softirq);
			assert(cnt == 8);
			top.nbCpu++;
		}
		cur = next;
	}
}

/*******************  FUNCTION  *********************/
char* TopWebNode::findEndOfLine(char* start, bool cutWithZero)
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
