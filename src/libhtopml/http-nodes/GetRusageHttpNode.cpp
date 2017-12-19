/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include "GetRusageHttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
GetRusageHttpNode::GetRusageHttpNode(const std::string& addr)
	: JsonHttpNode<rusage>(addr, &data)
{

}

/*******************  FUNCTION  *********************/
void GetRusageHttpNode::onRequest(const HttpRequest & request)
{
	getrusage(RUSAGE_SELF,&data);
}

/*******************  FUNCTION  *********************/
static int parseLine(char* line){
	int i = strlen(line);
	while (*line < '0' || *line > '9') line++;
	line[i-3] = '\0';
	i = atoi(line);
	return i;
}

/*******************  FUNCTION  *********************/
static int getMemUsage()
{
	FILE* file = fopen("/proc/self/status", "r");
	int result = -1;
	char line[128];


	while (fgets(line, 128, file) != NULL){
		if (strncmp(line, "VmRSS:", 6) == 0){
			result = parseLine(line);
			break;
		}
	}
	fclose(file);
	return result;
}

/*******************  FUNCTION  *********************/
void convertToJson(JsonState & json, const rusage & value)
{
	json.openStruct();
	json.printField("ru_utime",value.ru_utime);
	json.printField("ru_stime",value.ru_stime);
	json.printField("ru_maxrss",value.ru_maxrss);
	json.printField("ru_ixrss",value.ru_ixrss);
	json.printField("ru_idrss",value.ru_idrss);
	json.printField("ru_isrss",value.ru_isrss);
	json.printField("ru_minflt",value.ru_minflt);
	json.printField("ru_majflt",value.ru_majflt);
	json.printField("ru_nswap",value.ru_nswap);
	json.printField("ru_inblock",value.ru_inblock);
	json.printField("ru_oublock",value.ru_oublock);
	json.printField("ru_msgsnd",value.ru_msgsnd);
	json.printField("ru_msgrcv",value.ru_msgrcv);
	json.printField("ru_nsignals",value.ru_nsignals);
	json.printField("ru_nvcsw",value.ru_nvcsw);
	json.printField("ru_nivcsw",value.ru_nivcsw);
	int mem = getMemUsage();
	json.printField("memusage",mem);
	json.closeStruct();
}

/*******************  FUNCTION  *********************/
void convertToJson(JsonState & json, const timeval & value)
{
	json.openStruct();
	json.printField("tv_sec",(unsigned long)value.tv_sec);
	json.printField("tv_usec",(unsigned long)value.tv_usec);
	json.closeStruct();
}

}
