#include "heap.h"
#include "heap.c"
#include "heap_repl.h"

int main(void) {
    heap_init();
    malloc(16);
    void *p = calloc(4, 4);
    free(p);
    realloc(malloc(16), 32);
    free(p);
    realloc(p, 32);
    heap_check();
    return 0;
}
