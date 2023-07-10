#ifndef HEAP_REPL_H
#define HEAP_REPL_H

#define heap_init() heap_init(__FILE__, __LINE__)
#define heap_check() heap_check(__FILE__, __LINE__)
#define malloc(size) heap_malloc(__FILE__, __LINE__, size)
#define calloc(nmemb, size) heap_calloc(__FILE__, __LINE__, nmemb, size)
#define realloc(ptr, size) heap_realloc(__FILE__, __LINE__, ptr, size)
#define free(data) heap_free(__FILE__, __LINE__, data)

#endif
