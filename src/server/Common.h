/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <sstream>
#include <string>

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
template <class T> std::string toString(const T & value)
{
	std::stringstream str;
	str << value;
	return str.str();
}

};
