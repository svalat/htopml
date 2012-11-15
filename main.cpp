#include <iostream>
#include <cstdio>
#include "src/server/Server.h"
#include "src/server/ValidationWebNode.h"
#include "src/server/FileWebNode.h"
#include "src/server/CJsonWebNode.h"
#include "src/server/GnuplotWebNode.h"
#include "src/type_to_json/TypeToJson.h"
#include "src/web_nodes/LinuxGetRusage.h"

using namespace InternalHtmlSpyToolKit;
using namespace std;

struct Test
{
	int a;
	string b;
	float c;
	bool d;
	int e[8];
};

void typeToJson(JsonState & json,std::ostream& stream, const Test & value)
{
	json.openStruct();
	json.printField("a",value.a);
	json.printField("b",value.b);
	json.printField("c",value.c);
	json.printField("d",value.d);
	json.printFieldArray("e",value.e,8);
	json.closeStruct();
}

int main(int argc, char **argv)
{
	Test test = {10,"coucou",5.5,true};
	Server server(8080);
	cout << "init server on 8080" << endl;
	ValidationWebNode node("/index.html",true);
	ValidationWebNode nodeall("/images/",false);
	FileWebNode makefile("/Makefile","./Makefile","text/plain");
	CJsonWebNode<Test> jsonnode("/tmp",&test);
	GnuplotWebNode plot("/plot.png","plot x;");
	LinuxGetRusage rusageNode("/linux/rusage.js");
	server.registerWebNode(&node);
	server.registerWebNode(&nodeall);
	server.registerWebNode(&makefile);
	server.registerWebNode(&jsonnode);
	server.registerWebNode(&plot);
	server.registerWebNode(&rusageNode);
	server.start();
	cout << "running..." << endl;
	getchar();
	server.stop();
	cout << "stop." << endl;
	return 0;
}
