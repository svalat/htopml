/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include <cstring>
#include <string>
#include "FileHttpNode.h"
#include "ProcessHttpNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
ProcessHttpNode::ProcessHttpNode(const std::string& path, const std::string & mimetype)
	: HttpNode(path, true), mimetype()
{
	if (mimetype == "auto")
		this->mimetype = FileHttpNode::getMimeType(path);
}

/*******************  FUNCTION  *********************/
void ProcessHttpNode::onHttpRequest(HttpResponse & response,const HttpRequest & request)
{
	char * buffer = NULL;
	size_t size = 2048;
	size_t pos = 0;
	string cmd = genCommandOnRequest(request);
	FILE * fp = popen(cmd.c_str(),"r");
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
	response.setRawData(buffer,pos,true,genMimetypeOnEquest(request),200);
}

/*******************  FUNCTION  *********************/
string ProcessHttpNode::genMimetypeOnEquest(const HttpRequest& request)
{
	return mimetype;
}

/*******************  FUNCTION  *********************/
SimpleProcessHttpNode::SimpleProcessHttpNode(const string& path, const string& command, const string& mimetype)
	:ProcessHttpNode(path,mimetype), command(command)
{

}

/*******************  FUNCTION  *********************/
string SimpleProcessHttpNode::genCommandOnRequest(const HttpRequest& request)
{
	return command;
}

}
