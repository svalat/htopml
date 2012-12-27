/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#include "htopml-generic-values.h"

HtopmlNamedValueMap gblHtopmlNamedValueMap;

void htopml_update_generic_value(const std::string & name,double value)
{
	gblHtopmlNamedValueMap[name] = value;
}

extern "C" {
void htopml_update_generic_value(const char * name,double value)
{
	gblHtopmlNamedValueMap[name] = value;
}
}
