#ifndef HEAP_REPL_H
#define HEAP_REPL_H

#define malloc(size) heap_malloc(size)
#define calloc(nmemb, size) heap_calloc(nmemb, size)
#define realloc(ptr, size) heap_realloc(ptr, size)
#define free(data) heap_free(data)

#endif
