#ifndef HEAPCHECK_H
#define HEAPCHECK_H

#include <stdlib.h>

typedef struct heapcheck heapcheck;

struct heapcheck {
    void *ptr;
    const char *file;
    int line;
    size_t size;
    heapcheck *next;
};

void heapcheck_init(void);
void heapcheck_check(void);

void *heapcheck_malloc(const char *, int, size_t);
void *heapcheck_calloc(const char *, int, size_t, size_t);
void *heapcheck_realloc(const char *, int, void *, size_t);
void heapcheck_free(const char *, int, void *);

#endif
