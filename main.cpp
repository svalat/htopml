#include <iostream>
#include <cstdio>
#include "src/server/Server.h"
#include "src/server/ValidationWebNode.h"
#include "src/server/FileWebNode.h"
#include "src/type_to_json/TypeToJson.h"

using namespace InternalHtmlSpyToolKit;
using namespace std;

int main(int argc, char **argv)
{
	int lst[] = {10,20,30,40};
	typeToJson(cout,0,"test","coucou\" bob");
	typeToJson(cout,0,"test",lst,4);




	
	Server server(8080);
	cout << "init server on 8080" << endl;
	ValidationWebNode node("/index.html",true);
	ValidationWebNode nodeall("/images/",false);
	FileWebNode makefile("/Makefile","./Makefile","text/plain");
	server.registerWebNode(&node);
	server.registerWebNode(&nodeall);
	server.registerWebNode(&makefile);
	server.start();
	cout << "running..." << endl;
	getchar();
	server.stop();
	cout << "stop." << endl;
	return 0;
}
