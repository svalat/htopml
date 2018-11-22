/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <iostream>
#include <cstdio>
#include "HtopmlHttpServer.h"

/**********************  USING  *********************/
using namespace htopml;
using namespace std;

/*******************  FUNCTION  *********************/
int main(int argc, char **argv)
{
	htopml::glbAutomaticServer.start();
	getchar();
	return 0;
}
