/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0
             DATE     : 12/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <sstream>
#include <cassert>
#include <cstring>
#include "Common.h"
#include "TemplatePageHttpNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CONSTS  *********************/
static const char CST_TEMPL_HEAD_MARKER[] = "<!--IMPORT_USER_HEAD_HERE-->";
static const char CST_TEMPL_BODY_MARKER[] = "<!--IMPORT_USER_BODY_HERE-->";
static const char CST_USER_HEAD_START[] = "<head>";
static const char CST_USER_HEAD_END[] = "</head>";
static const char CST_USER_BODY_START[] = "<body>";
static const char CST_USER_BODY_END[] = "</body>";

/*******************  FUNCTION  *********************/
TemplatePageHttpNode::TemplatePageHttpNode(const string& mount, const string& contentFile, bool cache, const string& templateFile)
	: HttpNode(mount, true), templateFile(templateFile),contentFile(contentFile)
{
	this->cache = cache;
	if (templateFile.empty())
		this->templateFile = HTOPML_WWW_PATH "/theme/layout.htm";
}

/*******************  FUNCTION  *********************/
void TemplatePageHttpNode::onHttpRequest(HttpResponse & response,const HttpRequest & request)
{
	response.setMimeType("text/html");
	if (this->cache)
	{
		if (this->cacheContent.empty())
		{
			stringstream stream;
			load(stream);
			this->cacheContent = stream.str();
		}
		response.getStream() << this->cacheContent;
	} else {
		load(response.getStream());
	}
}

/*******************  FUNCTION  *********************/
void TemplatePageHttpNode::load(ostream& stream)
{
	//load files
	char * templ = loadFileInMemory(templateFile);
	char * user = loadFileInMemory(contentFile);

	//search insertion position for user <head> content
	char * templHeadPos = strstr(templ,CST_TEMPL_HEAD_MARKER);
	char * templBodyPos = strstr(templ,CST_TEMPL_BODY_MARKER);
	assert(templHeadPos != NULL);
	assert(templBodyPos != NULL);

	//setup final pieces from template
	char * outHeader = templ; *templHeadPos = '\0';
	char * outMiddle = templHeadPos + sizeof(CST_TEMPL_HEAD_MARKER) - 1; *templBodyPos = '\0';
	char * outFooter = templBodyPos + sizeof(CST_TEMPL_BODY_MARKER) - 1;

	//search pos into user data
	char * userHeadStart = strstr(user,CST_USER_HEAD_START);
	char * userHeadEnd = strstr(user,CST_USER_HEAD_END);
	char * userBodyStart = strstr(user,CST_USER_BODY_START);
	char * userBodyEnd = strstr(user,CST_USER_BODY_END);

	//errors
	assert(userHeadStart != NULL);
	assert(userHeadEnd != NULL);
	assert(userBodyStart != NULL);
	assert(userBodyEnd != NULL);

	//setup final peaces form template
	char * userHead = userHeadStart + sizeof(CST_USER_HEAD_START) - 1; *userHeadEnd = '\0';
	char * userBody = userBodyStart + sizeof(CST_USER_BODY_START) - 1; *userBodyEnd = '\0';

	//recompose the final file
	stream << outHeader << endl;
	stream << userHead << endl;
	stream << outMiddle << endl;
	stream << userBody << endl;
	stream << outFooter << endl;

	//free memory
	free(templ);
	free(user);
}

}
