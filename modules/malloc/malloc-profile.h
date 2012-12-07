#ifndef HTOPML_MALLOC_PROFILE_H
#define HTOPML_MALLOC_PROFILE_H

#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct htopml_malloc_stats_s
{
	bool init;
	pthread_spinlock_t lock;
	size_t malloc_nb;
	size_t cum_malloc_size;
	size_t min_malloc_size;
	size_t max_malloc_size;
	size_t free_nb;
	size_t realloc_nb;
	size_t cum_realloc_size;
	size_t calloc_nb;
	size_t cum_calloc_size;
};

extern struct htopml_malloc_stats_s htopml_malloc_stats;

#ifdef __cplusplus
}
#endif

#endif //HTOPML_MALLOC_PROFILE_H
