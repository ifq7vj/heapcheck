#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

typedef struct heap_t heap_t;

struct heap_t {
    const char *file;
    size_t line;
    void *ptr;
    size_t size;
    heap_t *next;
};

void heap_init(void);
void heap_check(void);

void *heap_malloc(const char *, size_t, size_t);
void *heap_calloc(const char *, size_t, size_t, size_t);
void *heap_realloc(const char *, size_t, void *, size_t);
void heap_free(const char *, size_t, void *);

#endif
