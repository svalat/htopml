/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include <cstring>
#include <string>
#include "GnuplotWebNode.h"

using namespace std;

/********************  NAMESPACE  *******************/
namespace InternalHtmlSpyToolKit
{

/*******************  FUNCTION  *********************/
GnuplotWebNode::GnuplotWebNode(const std::string& path, std::string command)
	: WebNode(path, true)
{
	this->command = command;
}

/*******************  FUNCTION  *********************/
WebNodeData GnuplotWebNode::getContent(mg_event event, mg_connection* conn, const mg_request_info* request_info)
{
	char * buffer = (char*)malloc(2048);
	size_t size = 2048;
	size_t pos = 0;
	string tmp = string("gnuplot -e \"set term png; set output;") + command + string("\"");
	FILE * fp = popen(tmp.c_str(),"r");
	if (fp == NULL)
		return WebNodeData((void*)"error",5,"text/plain",404);

	while (!feof(fp))
	{
		size_t s = fread(buffer+pos,1,2048,fp);
		if (s > 0)
		{
			pos+=s;
			size+=2048;
			buffer = (char*)realloc(buffer,size);
		}
	}
	return WebNodeData(buffer,size,"image/png",true);
}

}
