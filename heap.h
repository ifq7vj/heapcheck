#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

void heap_init(void);
void heap_check(void);
void *heap_malloc(size_t);
void *heap_calloc(size_t, size_t);
void *heap_realloc(void *, size_t);
void heap_free(void *);

#endif
