/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <unistd.h>
#include <libgen.h>
#include <sys/socket.h>
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

/********************  GLOBALS  *********************/
extern "C" {
	int gblHtopmlIsEnabled = htopml::HtopmlHttpServer::isEnabled();
}

/********************  NAMESPACE  *******************/
namespace htopml
{

/********************  GLOBALS  *********************/
/**
 * Global variable to force execution of constructor at loading time. By this
 * way we can start the internal server without actions from user.
 * It also be necessary for automatic registration of modules.
**/
#ifdef ENABLE_LISTEN_ALL
	HtopmlHttpServer glbAutomaticServer(8080,true);
#else
	HtopmlHttpServer glbAutomaticServer(8080,true,"127.0.0.1");
#endif

/*******************  FUNCTION  *********************/
/**
 * Constructor of htopml server class.
 * @param port Define the port to listen.
 * @param autostart If defined to true, automatically start the server.
 * @param listentAddr If not empty, open the listen port on the given network IP.
**/
HtopmlHttpServer::HtopmlHttpServer(int port,bool autostart, const std::string & listentAddr)
	:HttpServer(port,listentAddr),menu("/menu.js","navigation"),doubleMapNode("/generic/double-map.json")
{
	setupMenu();
	setupCommonRessources();
	setupTop();
	setupRusage();
	setupHowloc();

	if (passFileExist())
		this->setPasswordFile(getPassFile());

	if (autostart && gblHtopmlIsEnabled && instrumentThisExe())
	{
		if (!this->start())
			fprintf(stderr,"Failed to instrument %s\n",exeName.c_str());
		//avoid to start childs
		unsetenv("HTOPML_ENABLE");
	}/* else {
		fprintf(stderr,"Skip instrumtation of %s\n",exeName.c_str());
	}*/
}

/*******************  FUNCTION  *********************/
/**
 * Function to extract the current executable name.
 * It is used to know if we need to enable the server or not.
**/
std::string HtopmlHttpServer::getCurrentExeName(void ) const
{
	char buffer[4096];
	size_t size;
	size = readlink("/proc/self/exe",buffer,sizeof(buffer));
	assert(size < sizeof(buffer) - 1);
	buffer[size] = '\0';
	return basename(buffer);
}

/*******************  FUNCTION  *********************/
/**
 * Check if we need to instrument the current executable. The filter
 * if defined by HTOPML_INSTR_EXE environnement variable.
 * Return true if the variable is empty or match the current exe name.
**/
bool HtopmlHttpServer::instrumentThisExe(void )
{
	const char * fname = getenv("HTOPML_INSTR_EXE");
	exeName = getCurrentExeName();
	if (fname == NULL)
		return true;
	else
		return exeName == fname;
}

/*******************  FUNCTION  *********************/
/**
 * Return the path to the password file to use to protect the server.
**/
std::string HtopmlHttpServer::getPassFile(void ) const
{
	std::string res = getenv("HOME");
	res += "/.htopmlpass";
	return res;
}

/*******************  FUNCTION  *********************/
/**
 * Helper tp quicly check if the password file exist.
**/
bool HtopmlHttpServer::passFileExist(void ) const
{
	std::string file = getPassFile();
	//TODO use fstat which is cleaner for that (but less portable).
	FILE * fp = fopen(file.c_str(),"r");
	if (fp == NULL)
	{
		return false;
	} else {
		fclose(fp);
		return true;
	}
}

/*******************  FUNCTION  *********************/
/**
 * Register the menu http node in http server.
**/
void HtopmlHttpServer::setupMenu(void )
{
	this->registerHttpNode(menu);
}

/*******************  FUNCTION  *********************/
/**
 * Setup the mount points for default ressources common to all htopml
 * web UI infrastructure.
**/
void HtopmlHttpServer::setupCommonRessources(void )
{
	//basic ressources required for highcharts
	DirectoryHttpNode * ressourcesNode = new DirectoryHttpNode("/ressources/",HTOPML_EXTDEPS_PATH);
	ressourcesNode->registerFile("jquery/jquery.min.js");
	ressourcesNode->registerFile("d3js/d3.min.js");
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
	
	//double map node
	this->registerHttpNode(doubleMapNode);
}

/*******************  FUNCTION  *********************/
/**
 * Register a new entry in the htoml menu.
 * @param name Define the name of the entry (displayed text).
 * @param url Define the url of the menu entry. (eg. linux/htop.html)
 * @param icon If not empty, define the URL to the icon to display on the menu entry.
 **/
void HtopmlHttpServer::addMenuEntry(const std::string& name, const std::string& url, const std::string& icon)
{
	this->menu.addEntry(name,url,icon);
}

/*******************  FUNCTION  *********************/
/**
 * Setup the hwloc entries in server.
**/
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
	if (handler != NULL && gblHtopmlIsEnabled)
		handler(*this);
	return true;
}

/*******************  FUNCTION  *********************/
int HtopmlHttpServer::isEnabled(void )
{
	char * value = getenv("HTOPML_ENABLE");
	if (value != NULL && strncmp(value,"1",2) == 0)
	{
		return 1;
	} else {
		return 0;
	}
}

}

/*******************  FUNCTION  *********************/
extern "C" {
	void htopml_update_generic_value(const char* name, double value)
	{
		htopml::glbAutomaticServer.getDoubleMapNode().setValue(name,value);
	}
}
