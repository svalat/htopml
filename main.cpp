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
#include "src/server/FileWebNode.h"
#include "src/server/JsonWebNode.h"
#include "src/server/DirectoryWebNode.h"
#include "src/json/TypeToJson.h"
#include "src/web-nodes/GnuplotWebNode.h"
#include "src/web-nodes/GetRusageWebNode.h"
#include "src/web-nodes/TopWebNode.h"

/**********************  USING  *********************/
using namespace htopml;
using namespace std;

/********************  MACRO  ***********************/
#ifdef ENABLE_INSTR_LIB
	#define STATIC static
	#define main(x,y) main2(x,y)
#else
	#define STATIC
#endif

/*******************  FUNCTION  *********************/
void register_user_pages(Server & server)
{
	//this is to be overloadded by LD_PRELOAD of link
}

/*******************  FUNCTION  *********************/
int main(int argc, char **argv)
{
	STATIC Server server(8080);
	cout << "init server on 8080" << endl;

	//an example of draw directely from gnuplot
	server.registerWebNode(new GnuplotWebNode("/plot.png","plot x;"));

	//basic ressources required for highcharts
	STATIC DirectoryWebNode ressourcesNode("/ressources/","../extern-deps/");
	ressourcesNode.registerFile("jquery/jquery.min.js");
	ressourcesNode.registerFile("highcharts/js/highcharts.js");
	ressourcesNode.registerFile("highcharts/js/highcharts-more.js");
	ressourcesNode.registerFile("highcharts/js/modules/exporting.js");
	server.registerWebNode(&ressourcesNode);

	//fixed html pages
	server.quickRegisterFile("/linux/rusage.html","../src/www/linux/rusage.html");
	server.registerWebNode(new GetRusageWebNode("/linux/rusage.json"));

	//setup top structure
	server.quickRegisterFile("/linux/top.html","../src/www/linux/top.html");
	server.registerWebNode(new TopWebNode("/linux/top.json"));

	//some options
	server.setPasswordFile("./htpasswd");

	//register user pages
	register_user_pages(server);

	//run server
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
