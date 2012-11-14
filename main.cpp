#include <iostream>
#include <cstdio>
#include "src/server/Server.h"
#include "src/server/ValidationWebNode.h"
#include "src/server/FileWebNode.h"
#include "src/server/CJsonWebNode.h"
#include "src/server/GnuplotWebNode.h"
#include "src/type_to_json/TypeToJson.h"

using namespace InternalHtmlSpyToolKit;
using namespace std;

int main(int argc, char **argv)
{
	string tmp = "coucou";
	Server server(8080);
	cout << "init server on 8080" << endl;
	ValidationWebNode node("/index.html",true);
	ValidationWebNode nodeall("/images/",false);
	FileWebNode makefile("/Makefile","./Makefile","text/plain");
	CJsonWebNode<string> jsonnode("/tmp",&tmp);
	GnuplotWebNode plot("/plot.png","plot x;");
	server.registerWebNode(&node);
	server.registerWebNode(&nodeall);
	server.registerWebNode(&makefile);
	server.registerWebNode(&jsonnode);
	server.registerWebNode(&plot);
	server.start();
	cout << "running..." << endl;
	getchar();
	server.stop();
	cout << "stop." << endl;
	return 0;
}
