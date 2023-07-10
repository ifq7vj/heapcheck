#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct heap_t heap_t;

struct heap_t {
    const char *file;
    size_t line;
    void *data;
    size_t size;
    heap_t *prev;
    heap_t *next;
};

void heap_init(const char *, size_t);
void heap_check(const char *, size_t);
void *heap_malloc(const char *, size_t, size_t);
void *heap_calloc(const char *, size_t, size_t, size_t);
void *heap_realloc(const char *, size_t, void *, size_t);
void heap_free(const char *, size_t, void *);
static void heap_push(const char*, size_t, void *, size_t);
static void heap_remove(heap_t *);
static heap_t *heap_find(void *);

static heap_t *head;
static heap_t *tail;

void heap_init(const char *file, size_t line) {
    fprintf(stderr, "%s:%zu: call heap_init()\n", file, line);
    head = malloc(sizeof(heap_t));
    tail = malloc(sizeof(heap_t));
    assert(head != NULL && tail != NULL);
    head->next = tail;
    tail->prev = head;
    return;
}

void heap_check(const char *file, size_t line) {
    if (head == NULL) {
        fprintf(stderr, "%s:%zu: heap is not initialized\n", file, line);
        return;
    }
    fprintf(stderr, "%s:%zu: call heap_check()\n", file, line);
    heap_t *heap = head->next;
    while (heap != tail) {
        fprintf(stderr, "%s:%zu: memory leak [data: %p, size: %zu]\n", heap->file, heap->line, heap->data, heap->size);
        heap = heap->next;
    }
    return;
}

void *heap_malloc(const char *file, size_t line, size_t size) {
    if (head == NULL) {
        return malloc(size);
    }
    void *data = malloc(size);
    assert(data != NULL);
    heap_push(file, line, data, size);
    return data;
}

void *heap_calloc(const char *file, size_t line, size_t nmemb, size_t size) {
    if (head == NULL) {
        return calloc(nmemb, size);
    }
    void *data = calloc(nmemb, size);
    assert(data != NULL);
    heap_push(file, line, data, nmemb * size);
    return data;
}

void *heap_realloc(const char *file, size_t line, void *data, size_t size) {
    if (head == NULL) {
        return realloc(data, size);
    }
    heap_t *heap = heap_find(data);
    if (heap == NULL) {
        fprintf(stderr, "%s:%zu: invalid realloc [data: %p]\n", file, line, data);
        return NULL;
    }
    heap_remove(heap);
    data = realloc(data, size);
    assert(data != NULL);
    heap_push(file, line, data, size);
    heap->data = data;
    return data;
}

void heap_free(const char *file, size_t line, void *data) {
    if (head == NULL) {
        free(data);
        return;
    }
    heap_t *heap = heap_find(data);
    if (heap == NULL) {
        fprintf(stderr, "%s:%zu: invalid free [data: %p]\n", file, line, data);
        return;
    }
    heap_remove(heap);
    free(data);
    return;
}

void heap_push(const char *file, size_t line, void *data, size_t size) {
    heap_t *heap = malloc(sizeof(heap_t));
    assert(heap != NULL);
    heap->file = file;
    heap->line = line;
    heap->data = data;
    heap->size = size;
    heap->prev = tail->prev;
    heap->next = tail;
    tail->prev->next = heap;
    tail->prev = heap;
    return;
}

void heap_remove(heap_t *heap) {
    heap->prev->next = heap->next;
    heap->next->prev = heap->prev;
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
