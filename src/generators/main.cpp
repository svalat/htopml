#include <cstdio>
#include <htopml/HtopmlHttpServer.h>

#ifndef SKIP_HTOPML_MAIN
int main(void)
{
	htopml::glbAutomaticServer.start();
	getchar();
	return 0;
}
#endif //SKIP_HTOPML_MAIN
