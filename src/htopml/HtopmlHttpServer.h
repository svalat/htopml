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
#define REGISTER_TO_SERVER(handler) bool __call_handler_##handler = htopml::glbAutomaticServer.callHandler(handler)

/*********************  CLASS  **********************/
class HtopmlHttpServer : public HttpServer
{
	public:
		HtopmlHttpServer(int port,bool autostart = false,const std::string & listenAddr = "");
		void addMenuEntry(const std::string & name,const std::string & url,const std::string & icon = "");
		void addTemplatePage(const std::string & mount,const std::string & file,bool cache=true,const std::string icon = "");
		bool callHandler(void (*handler)(HtopmlHttpServer & server));
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
		MenuHttpNode menu;
		std::string exeName;
};

/********************  GLOBALS  *********************/
extern HtopmlHttpServer glbAutomaticServer;

}

#endif //HTOPML_HTOPML_HTTP_SERVER_H
