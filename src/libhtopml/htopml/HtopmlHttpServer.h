/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_HTOPML_HTTP_SERVER_H
#define HTOPML_HTOPML_HTTP_SERVER_H

/********************  HEADERS  *********************/
#include "HttpServer.h"
#include "MenuHttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/********************  MACRO  ***********************/
/**
 * Macro used to register a new module in htopml server at loading time (exe, dynlib...)
 * It's based on global object constructor mechanism.
 * @param handler Define a handler function to call to register the component.
**/
#define HTOPML_REGISTER_MODULE(handler) bool __call_handler_##handler = htopml::glbAutomaticServer.callHandler(handler)

/*********************  CLASS  **********************/
/**
 * Extension of basic HttpServer to provide all the default components and
 * registration system to build the htopml server. This class will be load
 * in a global variable to automatically start the server on application
 * startup.
**/
class HtopmlHttpServer : public HttpServer
{
	public:
		HtopmlHttpServer(int port,bool autostart = false,const std::string & listenAddr = "");
		void addMenuEntry(const std::string & name,const std::string & url,const std::string & icon = "");
		void addTemplatePage(const std::string & mount,const std::string & file,bool cache=true,const std::string icon = "");
		bool callHandler(void (*handler)(HtopmlHttpServer & server));
		static int isEnabled(void);
	private:
		bool instrumentThisExe(void);
		std::string getCurrentExeName(void) const;
		bool passFileExist(void) const;
		std::string getPassFile(void) const;
		void setupCommonRessources(void);
		void setupMenu(void);
		void setupTop(void);
		void setupRusage(void);
		void setupHowloc(void);
	private:
		/** Store the menu structure of the htopml infrastructure. **/
		MenuHttpNode menu;
		/** Name of the current executable. **/
		std::string exeName;
};

/********************  GLOBALS  *********************/
extern HtopmlHttpServer glbAutomaticServer;
extern "C" {
extern int gblHtopmlIsEnabled;
}

}

#endif //HTOPML_HTOPML_HTTP_SERVER_H
