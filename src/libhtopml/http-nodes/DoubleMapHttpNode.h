/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.2.0
             DATE     : 12/2017
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
