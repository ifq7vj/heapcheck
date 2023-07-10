#include "heap.h"
#include "heap.c"
#include "heap_repl.h"

int main(void) {
    heap_init();
    malloc(16);
    heap_check();
    return 0;
}
