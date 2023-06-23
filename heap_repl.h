#ifndef HEAP_REPL_H
#define HEAP_REPL_H

#include "heap.h"

#define malloc(size) heap_malloc(__FILE__, __LINE__, (size))
#define calloc(n, size) heap_calloc(__FILE__, __LINE__, (n), (size))
#define realloc(ptr, size) heap_realloc(__FILE__, __LINE__, (ptr), (size))
#define free(ptr) heap_free(__FILE__, __LINE__, (ptr))

#endif
