/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include <cstring>
#include <string>
#include "GnuplotHttpNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
GnuplotHttpNode::GnuplotHttpNode(const std::string& path, const std::string & command)
	: ProcessHttpNode(path,"auto")
{
}

/*******************  FUNCTION  *********************/
string GnuplotHttpNode::genCommandOnRequest(const HttpRequest& request)
{
	return string("gnuplot -e \"set term png; set output;") + command + string("\"");
}

}
