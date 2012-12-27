/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_GENERIC_VALUES_H
#define HTOPML_GENERIC_VALUES_H

#ifdef __cplusplus
#include <string>
#include <map>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void htopml_update_generic_value(const char * name,double value);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
typedef std::map<std::string,double> HtopmlNamedValueMap;
extern HtopmlNamedValueMap gblHtopmlNamedValueMap;
void htopml_update_generic_value(const std::string & name,double value);
#endif

#endif //HTOPML_GENERIC_VALUES_H
