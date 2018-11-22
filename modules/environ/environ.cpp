#include "environ.h"
#include <unistd.h>

static const char * find_value_start(char * capture_name,const char * str,size_t maxSize)
{
	int i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		capture_name[i] = str[i];
		i++;
		assert(i < maxSize);
	}
	capture_name[i] = '\0';

	if (str[i] == '=')
		return str+i+1;
	else
		return str+i;
}

void convertToJson(htopml::JsonState& json, environ_c_array value)
{
	int i = 0;
	const char * fieldValue;
	char name[512];
	json.openStruct();
	while (environ[i] != NULL)
	{
		fieldValue = find_value_start(name,environ[i++],sizeof(name));
		json.printField(name,fieldValue);
	}
	json.closeStruct();
}
