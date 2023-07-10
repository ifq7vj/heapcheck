#include "heap.h"
#include "heap.c"
#include "heap_repl.h"

int main(void) {
    heap_init();
    malloc(16);
    free(calloc(4, 4));
    realloc(malloc(16), 32);
    heap_check();
    return 0;
}
