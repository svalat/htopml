#include <iostream>
#include <cstdio>
#include "src/Server.h"
#include "src/ValidationWebNode.h"
#include "src/FileWebNode.h"

using namespace InternalHtmlSpyToolKit;
using namespace std;

int main(int argc, char **argv)
{
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
