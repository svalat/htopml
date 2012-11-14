/*****************************************************
             PROJECT  : InternalHtmlSpyToolKit (IHSTK)
             VERSION  : 0.0.0
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#include <sstream>
#include <string>

namespace InternalHtmlSpyToolKit
{

template <class T> std::string toString(const T & value)
{
	std::stringstream str;
	str << value;
	return str.str();
}

};
