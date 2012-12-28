/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include "DoubleMapHttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
DoubleMapHttpNode::DoubleMapHttpNode(const std::string& addr) 
	:JsonHttpNode< htopml::DoubleMap >(addr,&data)
{
}

/*******************  FUNCTION  *********************/
void DoubleMapHttpNode::setValue(const char* name, double value)
{
	this->data[name] = value;
}

/*******************  FUNCTION  *********************/
void DoubleMapHttpNode::setValue(const std::string& name, double value)
{
	this->data[name] = value;
}

/*******************  FUNCTION  *********************/
double* DoubleMapHttpNode::getValuePointer(const char* name)
{
	return &(this->data[name]);
}

/*******************  FUNCTION  *********************/
double* DoubleMapHttpNode::getValuePointer(const std::string& name)
{
	return &(this->data[name]);
}

}
