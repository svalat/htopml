/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include <cstring>
#include <string>
#include "GnuplotWebNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
GnuplotWebNode::GnuplotWebNode(const std::string& path, const std::string & command)
	: WebNode(path, true), command(command)
{
}

/*******************  FUNCTION  *********************/
void GnuplotWebNode::getContent(Response & response,const Request & request)
{
	char * buffer = NULL;
	size_t size = 2048;
	size_t pos = 0;
	string tmp = string("gnuplot -e \"set term png; set output;") + command + string("\"");
	FILE * fp = popen(tmp.c_str(),"r");
	if (fp == NULL)
	{
		response.error(404,"error");
		return;
	}

	//prepare buffer
	buffer = (char*)malloc(2048);

	//read the stream until end
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

	fclose(fp);

	//setup answer
	response.setRawData(buffer,size,true,"image/png",200);
}

}
