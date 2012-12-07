#include <cstdio>
#include <sys/types.h>
#include <dirent.h>
#include <cassert>
#include <unistd.h>
#include "openedfiles.h"

using namespace std;

HtopmlFileList htopmlGetOpenFileList(void )
{
	//vars
	DIR * dir;
	dirent * dirent;
	int cnt = 0;
	HtopmlFileList res;
	char buffer[4096];
	size_t tmp;
	string absPath;

	//open proc dir
	dir = opendir("/proc/self/fd");
	assert(dir != NULL);//TODO : transform to assume

	while ((dirent = readdir(dir)) != NULL)
	{
		if (dirent->d_name[0] != '.' && dirent->d_name[1] != '\0')
		{
			absPath  = "/proc/self/fd/";
			absPath += dirent->d_name;
			tmp = readlink(absPath.c_str(),buffer,sizeof(buffer));
			if (tmp > 0 && tmp <= sizeof(buffer))
			{
				buffer[tmp] = '\0';
				res.push_back(buffer);
			}
		}
	}

	//finish
	closedir(dir);

	return res;
}
