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
#include "src/htopml/HtopmlHttpServer.h"

/**********************  USING  *********************/
using namespace htopml;
using namespace std;

/*******************  FUNCTION  *********************/
int main(int argc, char **argv)
{
	cout << "init server on 8080" << endl;
	HtopmlHttpServer server(8080);
	server.addMenuEntry("dsf","sd");
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
