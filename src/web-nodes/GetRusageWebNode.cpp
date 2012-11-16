/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include "GetRusageWebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
GetRusageWebNode::GetRusageWebNode(const std::string& addr)
	: JsonWebNode<rusage>(addr, &data)
{

}

/*******************  FUNCTION  *********************/
void GetRusageWebNode::onRequest(const mg_request_info* request_info)
{
	getrusage(RUSAGE_SELF,&data);
}

static int parseLine(char* line){
	int i = strlen(line);
	while (*line < '0' || *line > '9') line++;
	line[i-3] = '\0';
	i = atoi(line);
	return i;
}


static int getMemUsage(){ //Note: this value is in KB!
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
void typeToJson(JsonState & json,std::ostream& stream, const rusage & value)
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
void typeToJson(JsonState & json,std::ostream& stream, const timeval & value)
{
	json.openStruct();
	json.printField("tv_sec",(unsigned long)value.tv_sec);
	json.printField("tv_usec",(unsigned long)value.tv_usec);
	json.closeStruct();
}

}
