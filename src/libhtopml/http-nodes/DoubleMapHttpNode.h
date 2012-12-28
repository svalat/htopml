/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_DOUBLE_MAP_HTTP_NODE_H
#define HTOPML_DOUBLE_MAP_HTTP_NODE_H

/********************  HEADERS  *********************/
#include <map>
#include "JsonHttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
typedef std::map<std::string,double> DoubleMap;

/*********************  CLASS  **********************/
class DoubleMapHttpNode : public JsonHttpNode<DoubleMap>
{
	public:
		DoubleMapHttpNode(const std::string & addr);
		void setValue(const char * name,double value);
		void setValue(const std::string & name,double value);
		double * getValuePointer(const char * name);
		double * getValuePointer(const std::string & name);
	private:
		DoubleMap data;
};

}

#endif // HTOPML_DOUBLE_MAP_HTTP_NODE_H
