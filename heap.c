#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct heap_t heap_t;

struct heap_t {
    void *data;
    heap_t *next;
};

void heap_init(void);
void heap_check(void);
void *heap_malloc(size_t);
static void heap_push(void *);
static void heap_warn(void *);

static heap_t *head;
static heap_t *tail;

void heap_init(void) {
    head = malloc(sizeof(heap_t));
    tail = head;
    return;
}

void heap_check(void) {
    heap_t *heap = head;
    head = head->next;
    free(heap);
    while (head != NULL) {
        heap = head;
        head = head->next;
        heap_warn(heap->data);
        free(heap->data);
        free(heap);
    }
    return;
}

void *heap_malloc(size_t size) {
    if (head == NULL) {
        return malloc(size);
    }
    void *data = malloc(size);
    heap_push(data);
    return data;
}

void heap_push(void *data) {
    heap_t *heap = malloc(sizeof(heap_t));
    tail->next = heap;
    tail = tail->next;
    tail->data = data;
    return;
}

void heap_warn(void *data) {
    fprintf(stderr, "%p\n", data);
    return;
}
