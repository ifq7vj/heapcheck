#ifndef malloc
#define malloc(size) heapcheck_malloc(__FILE__, __LINE__, (size))
#endif

#ifndef calloc
#define calloc(n, size) heapcheck_calloc(__FILE__, __LINE__, (n), (size))
#endif

#ifndef realloc
#define realloc(ptr, size) heapcheck_realloc(__FILE__, __LINE__, (ptr), (size))
#endif

#ifndef free
#define free(ptr) heapcheck_free(__FILE__, __LINE__, (ptr))
#endif
