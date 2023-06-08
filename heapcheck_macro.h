#ifndef calloc
#define calloc(n, size) heapcheck_calloc(__FILE__, __LINE__, (n), (size))
#endif

#ifndef free
#define free(ptr) heapcheck_free(__FILE__, __LINE__, (ptr))
#endif
