#include <iostream>
#include <cstdio>
#include "src/server/Server.h"
#include "src/server/ValidationWebNode.h"
#include "src/server/FileWebNode.h"
#include "src/server/CJsonWebNode.h"
#include "src/server/GnuplotWebNode.h"
#include "src/type_to_json/TypeToJson.h"
#include "src/web_nodes/LinuxGetRusage.h"
#include "src/web_nodes/DirectoryWebNode.h"

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

int main2(int argc, char **argv)
{
	static Test test = {10,"coucou",5.5,true};
	static Server server(8080);
	cout << "init server on 8080" << endl;
	static ValidationWebNode node("/index.html",true);
	static ValidationWebNode nodeall("/images/",false);
	static FileWebNode makefile("/Makefile","./Makefile","text/plain");
	static CJsonWebNode<Test> jsonnode("/tmp",&test);
	static GnuplotWebNode plot("/plot.png","plot x;");
	static LinuxGetRusage rusageNode("/linux/rusage.json");
	static FileWebNode rusage_html("/linux/rusage.html","../src/www/rusage.html","text/html");
	static FileWebNode test_json("/linux/test.json","../src/www/test.json","application/json");
	static DirectoryWebNode ressourcesNode("/ressources/","../extern_deps/");
	ressourcesNode.registerFile("jquery/jquery.min.js","application/javascript");
	ressourcesNode.registerFile("highcharts/js/highcharts.js","application/javascript");
	ressourcesNode.registerFile("highcharts/js/highcharts-more.js","application/javascript");
	ressourcesNode.registerFile("highcharts/js/modules/exporting.js","application/javascript");
	
	server.registerWebNode(&node);
	server.registerWebNode(&nodeall);
	server.registerWebNode(&makefile);
	server.registerWebNode(&jsonnode);
	server.registerWebNode(&plot);
	server.registerWebNode(&rusageNode);
	server.registerWebNode(&ressourcesNode);
	server.registerWebNode(&rusage_html);
	server.registerWebNode(&test_json);
	server.start();
	cout << "running..." << endl;
// 	getchar();
// 	server.stop();
// 	cout << "stop." << endl;
	return 0;
}

int tmp = main2(0,NULL);
