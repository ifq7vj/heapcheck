#include <stdlib.h>
#include "heap.h"

typedef struct heap_t heap_t;

struct heap_t {
    void *data;
    heap_t *next;
};

static heap_t *head;
static heap_t *tail;

void heap_init(void) {
    tail = head = malloc(sizeof(heap_t));
    return;
}

void heap_check(void) {
    free(head);
    return;
}
