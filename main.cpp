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
#include "src/server/HttpServer.h"
#include "src/server/FileHttpNode.h"
#include "src/server/JsonHttpNode.h"
#include "src/server/DirectoryHttpNode.h"
#include "src/server/TemplatePageHttpNode.h"
#include "src/server/MenuHttpNode.h"
#include "src/json/TypeToJson.h"
#include "src/http-nodes/GnuplotHttpNode.h"
#include "src/http-nodes/GetRusageHttpNode.h"
#include "src/http-nodes/TopHttpNode.h"

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
#ifndef SKEEP_DEFAULT_USER_PAGES
void register_user_pages(HttpServer & server)
{
	//this is to be overloadded by LD_PRELOAD of link
}
#else
void register_user_pages(HttpServer & server);
#endif

/*******************  FUNCTION  *********************/
int main(int argc, char **argv)
{
	STATIC HttpServer server(8080);
	cout << "init server on 8080" << endl;

	//an example of draw directely from gnuplot
	server.registerHttpNode(new GnuplotHttpNode("/plot.png","plot x;"));

	//basic ressources required for highcharts
	STATIC DirectoryHttpNode ressourcesNode("/ressources/","../extern-deps/");
	ressourcesNode.registerFile("jquery/jquery.min.js");
	ressourcesNode.registerFile("highcharts/js/highcharts.js");
	ressourcesNode.registerFile("highcharts/js/highcharts-more.js");
	ressourcesNode.registerFile("highcharts/js/modules/exporting.js");
	ressourcesNode.registerFile("highcharts/js/themes/gray.js");
	server.registerHttpNode(&ressourcesNode);

	//theme node
	STATIC DirectoryHttpNode themeNode("/theme/","../src/www/theme/");
	themeNode.registerFile("body.jpg");
	themeNode.registerFile("header.jpg");
	themeNode.registerFile("menu_hover.png");
	themeNode.registerFile("htopml.css",false);
	themeNode.registerFile("layout.htm",false);
	themeNode.registerFile("htopml.js",false);
	server.registerHttpNode(&themeNode);

	//icon nodes
	STATIC DirectoryHttpNode iconsNode("/theme/icons/","../src/www/theme/icons/");
	iconsNode.registerFile("aboutus.png");
	iconsNode.registerFile("contact.png");
	iconsNode.registerFile("home.png");
	iconsNode.registerFile("portfolio.png");
	iconsNode.registerFile("services.png");
	iconsNode.registerFile("unknown.png");
	themeNode.registerChildNode(iconsNode);

	//fixed html pages
	server.registerHttpNode(new TemplatePageHttpNode("/linux/rusage.html","../src/www/linux/rusage.html"));
	server.registerHttpNode(new GetRusageHttpNode("/linux/rusage.json"));

	//setup top structure
	server.registerHttpNode(new TemplatePageHttpNode("/linux/top.html","../src/www/linux/top.html"));
	server.registerHttpNode(new TopHttpNode("/linux/top.json"));

	//setup menu
	MenuHttpNode * menu = new MenuHttpNode("/menu.js","navigation");
	menu->addEntry("Top","/linux/top.html");
	menu->addEntry("Getrusage","/linux/rusage.html");
	server.registerHttpNode(menu);

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
