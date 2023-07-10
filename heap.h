#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

void heap_init(const char *, size_t);
void heap_check(const char *, size_t);
void *heap_malloc(const char *, size_t, size_t);
void *heap_calloc(const char *, size_t, size_t, size_t);
void *heap_realloc(const char *, size_t, void *, size_t);
void heap_free(const char *, size_t, void *);

#endif
