#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct heap_t heap_t;

struct heap_t {
    void *data;
    heap_t *prev;
    heap_t *next;
};

void heap_init(void);
void heap_check(void);
void *heap_malloc(size_t);
void *heap_calloc(size_t, size_t);
void *heap_realloc(void *, size_t);
void heap_free(void *);
static void heap_push(void *);
static void heap_remove(heap_t *);
static heap_t *heap_find(void *);
static void heap_warn(void *);

static heap_t *head;
static heap_t *tail;

void heap_init(void) {
    head = malloc(sizeof(heap_t));
    tail = malloc(sizeof(heap_t));
    assert(head != NULL && tail != NULL);
    head->next = tail;
    tail->prev = head;
    return;
}

void heap_check(void) {
    heap_t *heap = head->next;
    while (heap != tail) {
        heap_warn(heap->data);
        heap = heap->next;
    }
    return;
}

void *heap_malloc(size_t size) {
    if (head == NULL) {
        return malloc(size);
    }
    void *data = malloc(size);
    assert(data != NULL);
    heap_push(data);
    return data;
}

void *heap_calloc(size_t nmemb, size_t size) {
    if (head == NULL) {
        return calloc(nmemb, size);
    }
    void *data = calloc(nmemb, size);
    assert(data != NULL);
    heap_push(data);
    return data;
}

void *heap_realloc(void *data, size_t size) {
    if (head == NULL) {
        return realloc(data, size);
    }
    heap_t *heap = heap_find(data);
    if (heap == NULL) {
        return NULL;
    }
    data = realloc(data, size);
    assert(data != NULL);
    heap->data = data;
    return data;
}

void heap_free(void *data) {
    if (head == NULL) {
        free(data);
        return;
    }
    heap_t *heap = heap_find(data);
    if (heap == NULL) {
        return;
    }
    heap_remove(heap);
    return;
}

void heap_push(void *data) {
    heap_t *heap = malloc(sizeof(heap_t));
    assert(heap != NULL);
    heap->data = data;
    heap->prev = tail->prev;
    heap->next = tail;
    tail->prev->next = heap;
    tail->prev = heap;
    return;
}

void heap_remove(heap_t *heap) {
    heap->prev->next = heap->next;
    heap->next->prev = heap->prev;
    free(heap->data);
    free(heap);
    return;
}

heap_t *heap_find(void *data) {
    heap_t *heap = head->next;
    while (heap != tail) {
        if (heap->data == data) {
            return heap;
        }
        heap = heap->next;
    }
    return NULL;
}

void heap_warn(void *data) {
    fprintf(stderr, "%p\n", data);
    return;
}
