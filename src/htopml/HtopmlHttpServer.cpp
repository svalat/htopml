/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include "DirectoryHttpNode.h"
#include "TemplatePageHttpNode.h"
#include "GetRusageHttpNode.h"
#include "TopHttpNode.h"
#include "ProcessHttpNode.h"
#include "HtopmlHttpServer.h"
//optional
#ifdef HAVE_HWLOC
#include "HwlocThreadBindingHttpNode.h"
#endif //HAVE_HWLOC

/********************  NAMESPACE  *******************/
namespace htopml
{

/********************  GLOBALS  *********************/
HtopmlHttpServer glbAutomaticServer(8080,true);

/*******************  FUNCTION  *********************/
HtopmlHttpServer::HtopmlHttpServer(int port,bool autostart)
	:HttpServer(port),menu("/menu.js","navigation")
{
	setupMenu();
	setupCommonRessources();
	setupTop();
	setupRusage();
	setupHowloc();

	this->setPasswordFile("./htpasswd");

	if (autostart)
		this->start();
}

/*******************  FUNCTION  *********************/
void HtopmlHttpServer::setupMenu(void )
{
	this->registerHttpNode(menu);
}

/*******************  FUNCTION  *********************/
void HtopmlHttpServer::setupCommonRessources(void )
{
	//basic ressources required for highcharts
	DirectoryHttpNode * ressourcesNode = new DirectoryHttpNode("/ressources/",HTOPML_EXTDEPS_PATH);
	ressourcesNode->registerFile("jquery/jquery.min.js");
	ressourcesNode->registerFile("highcharts/js/highcharts.js");
	ressourcesNode->registerFile("highcharts/js/highcharts-more.js");
	ressourcesNode->registerFile("highcharts/js/modules/exporting.js");
	ressourcesNode->registerFile("highcharts/js/themes/gray.js");
	this->registerHttpNode(ressourcesNode);

	//theme node
	DirectoryHttpNode * themeNode = new DirectoryHttpNode("/theme/",HTOPML_WWW_PATH "/theme/");
	themeNode->registerFile("body.jpg");
	themeNode->registerFile("header.jpg");
	themeNode->registerFile("menu_hover.png");
	themeNode->registerFile("htopml.css",false);
	themeNode->registerFile("layout.htm",false);
	themeNode->registerFile("htopml.js",false);
	this->registerHttpNode(themeNode);

	//common js
	this->quickRegisterFile("/common.js",HTOPML_WWW_PATH "/common.js");

	//icon nodes
	DirectoryHttpNode * iconsNode = new DirectoryHttpNode("/theme/icons/",HTOPML_WWW_PATH "/theme/icons/");
	iconsNode->registerFile("home.png");
	iconsNode->registerFile("unknown.png");
	themeNode->registerChildNode(iconsNode);

	//set home pages
	addTemplatePage("/index.htm",HTOPML_WWW_PATH "/index.htm",false);
	menu.addEntry("Home","/index.htm","/theme/icons/home.png");
	setHomepage("/index.htm");
}

/*******************  FUNCTION  *********************/
void HtopmlHttpServer::addMenuEntry(const std::string& name, const std::string& url, const std::string& icon)
{
	this->menu.addEntry(name,url,icon);
}

/*******************  FUNCTION  *********************/
void HtopmlHttpServer::setupHowloc(void )
{
	//setup top structure
	this->registerHttpNode(new SimpleProcessHttpNode("/linux/hwloc.txt","lstopo --of console"));
	this->registerHttpNode(new SimpleProcessHttpNode("/linux/hwloc.xml","lstopo --of xml"));
	this->registerHttpNode(new SimpleProcessHttpNode("/linux/hwloc.svg","lstopo --of native_svg"));
	this->registerHttpNode(new SimpleProcessHttpNode("/linux/hwloc.png","lstopo --of png"));

	//setup hwloc node
	#ifdef HAVE_HWLOC
	this->registerHttpNode(new HwlocThreadBindingHttpNode("/linux/hwloc-thread-binding.json"));
	this->quickRegisterFile("/linux/binding.png",HTOPML_WWW_PATH "/linux/binding.png");
	addTemplatePage("/linux/binding.html",HTOPML_WWW_PATH "/linux/binding.html",false);

	//register menu entry
	menu.addEntry("binding","/linux/binding.html","/linux/binding.png");
	#endif //HAVE_HWLOC
}

/*******************  FUNCTION  *********************/
void HtopmlHttpServer::setupRusage(void )
{
	//fixed html pages
	this->registerHttpNode(new GetRusageHttpNode("/linux/rusage.json"));

	//add page
	addTemplatePage("/linux/rusage.html",HTOPML_WWW_PATH "/linux/rusage.html");

	//register menu entry
	menu.addEntry("Getrusage","/linux/rusage.html");
}

/*******************  FUNCTION  *********************/
void HtopmlHttpServer::setupTop(void )
{
	//setup top structure
	this->registerHttpNode(new TopHttpNode("/linux/top.json"));

	//add page
	this->quickRegisterFile("/linux/top.png",HTOPML_WWW_PATH "/linux/top.png");
	this->addTemplatePage("/linux/top.html",HTOPML_WWW_PATH "/linux/top.html");

	//register menu entry
	menu.addEntry("Top","/linux/top.html","/linux/top.png");
}

/*******************  FUNCTION  *********************/
void HtopmlHttpServer::addTemplatePage(const std::string& mount, const std::string& file, bool cache, const std::string icon)
{
	this->registerHttpNode(new TemplatePageHttpNode(mount,file,cache));
}

/*******************  FUNCTION  *********************/
bool HtopmlHttpServer::callHandler(void (*handler)(HtopmlHttpServer & server))
{
	assert(handler != NULL);
	if (handler != NULL)
		handler(*this);
	return true;
}

}
