/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <iostream>
#include <cstdio>
#include "src/server/Server.h"
#include "src/server/ValidationWebNode.h"
#include "src/server/FileWebNode.h"
#include "src/server/JsonWebNode.h"
#include "src/server/DirectoryWebNode.h"
#include "src/json/TypeToJson.h"
#include "src/web-nodes/GnuplotWebNode.h"
#include "src/web-nodes/GetRusageWebNode.h"

/**********************  USING  *********************/
using namespace htopml;
using namespace std;

/*********************  STRUCT  *********************/
struct Test
{
	int a;
	string b;
	float c;
	bool d;
	int e[8];
};

/*******************  FUNCTION  *********************/
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

/********************  MACRO  ***********************/
#ifdef ENABLE_INSTR_LIB
	#define STATIC static
	#define main(x,y) main2(x,y)
#else
	#define STATIC
#endif

/*******************  FUNCTION  *********************/
int main(int argc, char **argv)
{
	STATIC Test test = {10,"coucou",5.5,true};
	STATIC Server server(8080);
	cout << "init server on 8080" << endl;
	STATIC ValidationWebNode node("/index.html",true);
	STATIC ValidationWebNode nodeall("/images/",false);
	STATIC FileWebNode makefile("/Makefile","./Makefile","text/plain");
	STATIC JsonWebNode<Test> jsonnode("/tmp",&test);
	STATIC GnuplotWebNode plot("/plot.png","plot x;");
	STATIC GetRusageWebNode rusageNode("/linux/rusage.json");
	STATIC FileWebNode rusage_html("/linux/rusage.html","../src/www/rusage.html","text/html");
	STATIC FileWebNode test_json("/linux/test.json","../src/www/test.json","application/json");
	STATIC DirectoryWebNode ressourcesNode("/ressources/","../extern-deps/");
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
	server.setPasswordFile("./htpasswd");
	server.start();
	cout << "running..." << endl;
	#ifndef ENABLE_INSTR_LIB
	getchar();
	server.stop();
	cout << "stop." << endl;
	#endif
	return 0;
}

#ifdef ENABLE_INSTR_LIB
int tmp = main2(0,NULL);
#endif
