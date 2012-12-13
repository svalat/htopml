#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>
#include "malloc-profile.h"

struct htopml_malloc_stats_s htopml_malloc_stats = {false};
static char calloc_dlsym_buffer[1024];

void htopml_malloc_stat_init(void)
{
	//already done
	if (htopml_malloc_stats.init)
		return;

	pthread_spin_init(&htopml_malloc_stats.lock,PTHREAD_SCOPE_PROCESS);

	htopml_malloc_stats.malloc_nb          = 0;
	htopml_malloc_stats.cum_malloc_size    = 0;
	htopml_malloc_stats.min_malloc_size    = -1;
	htopml_malloc_stats.max_malloc_size    = 0;
	htopml_malloc_stats.free_nb            = 0;
	htopml_malloc_stats.init = true;
}

void* malloc(size_t size)
{
	//setup wrapper subcall
	static void* (*orig_malloc)(size_t) = NULL;
	if (!orig_malloc)
		orig_malloc = (void* (*)(size_t))  dlsym(RTLD_NEXT, "malloc");  /* returns the object reference for malloc */

	//call orig
	void *p = orig_malloc(size);               /* call malloc() using function pointer */

	//if counter not init
	if (htopml_malloc_stats.init == false)
		htopml_malloc_stat_init();

	//count
	pthread_spin_lock(&htopml_malloc_stats.lock);
	htopml_malloc_stats.malloc_nb++;
	htopml_malloc_stats.cum_malloc_size+=size;
	if (size < htopml_malloc_stats.min_malloc_size) htopml_malloc_stats.min_malloc_size = size;
	if (size > htopml_malloc_stats.max_malloc_size) htopml_malloc_stats.max_malloc_size = size;
	pthread_spin_unlock(&htopml_malloc_stats.lock);
	
	return p;
}

void free(void * ptr)
{
	//setup wrapper subcall
	static void (*orig_free)(void * ptr) = NULL;
	if (!orig_free)
		orig_free =  (void (*)(void * ptr))dlsym(RTLD_NEXT, "free");  /* returns the object reference for free */

	//call orig
	orig_free(ptr);               /* call free() using function pointer */

	//if counter not init
	if (htopml_malloc_stats.init == false)
		htopml_malloc_stat_init();

	//count
	pthread_spin_lock(&htopml_malloc_stats.lock);
	htopml_malloc_stats.free_nb++;
	pthread_spin_unlock(&htopml_malloc_stats.lock);
}

void * realloc (void * ptr, size_t size)
{
	//setup wrapper subcall
	static void * (*orig_realloc)(void * ptr,size_t size) = NULL;
	if (!orig_realloc)
		orig_realloc = ( void * (*)(void * ptr,size_t size)) dlsym(RTLD_NEXT, "realloc");  /* returns the object reference for free */

	//call orig
	ptr = orig_realloc(ptr,size);               /* call free() using function pointer */

	//if counter not init
	if (htopml_malloc_stats.init == false)
		htopml_malloc_stat_init();

	//count
	pthread_spin_lock(&htopml_malloc_stats.lock);
	htopml_malloc_stats.realloc_nb++;
	htopml_malloc_stats.cum_realloc_size+=size;
	if (size < htopml_malloc_stats.min_malloc_size) htopml_malloc_stats.min_malloc_size = size;
	if (size > htopml_malloc_stats.max_malloc_size) htopml_malloc_stats.max_malloc_size = size;
	pthread_spin_unlock(&htopml_malloc_stats.lock);

	return ptr;
}

void* calloc(size_t nmemb,size_t size)
{
	//setup wrapper subcall
	static void* (*orig_calloc)(size_t,size_t) = NULL;
	if (orig_calloc == NULL)
	{
		orig_calloc = ( void* (*)(size_t,size_t))1;
		orig_calloc =  ( void* (*)(size_t,size_t))dlsym(RTLD_NEXT, "calloc");  /* returns the object reference for malloc */
	} else if (orig_calloc ==  ( void* (*)(size_t,size_t))1) {
		return calloc_dlsym_buffer;
	}

	//call orig
	void *p = orig_calloc(nmemb,size);               /* call malloc() using function pointer */

	//if counter not init
	if (htopml_malloc_stats.init == false)
		htopml_malloc_stat_init();

	//count
	pthread_spin_lock(&htopml_malloc_stats.lock);
	htopml_malloc_stats.calloc_nb++;
	htopml_malloc_stats.cum_calloc_size+=size;
	if (size < htopml_malloc_stats.min_malloc_size) htopml_malloc_stats.min_malloc_size = size;
	if (size > htopml_malloc_stats.max_malloc_size) htopml_malloc_stats.max_malloc_size = size;
	pthread_spin_unlock(&htopml_malloc_stats.lock);

	return p;
}
