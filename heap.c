#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

static heap_t *head = NULL;

static void heap_warn(const char *file, int line, void *ptr, size_t size, const char *msg) {
    fprintf(stderr, "heap: %s [file: %s, line: %d, ptr: %p, size: %zu]\n", msg, file, line, ptr, size);
    return;
}

static void heap_push(const char *file, int line, void *ptr, size_t size) {
    heap_t *heap = calloc(1, sizeof(heap_t));
    if (!heap) { fprintf(stderr, "heap: push failed\n"); return; }
    heap->file = file; heap->line = line; heap->ptr = ptr; heap->size = size;
    heap->next = head->next; head->next = heap;
    return;
}

static void heap_delete(void *ptr) {
    for (heap_t *heap = head; heap->next; heap = heap->next) {
        if (heap->next->ptr == ptr) {
            heap_t *tmp = heap->next; heap->next = tmp->next; free(tmp);
            return;
        }
    }
    fprintf(stderr, "heap: not found\n");
    return;
}

void heap_init(void) {
    fprintf(stderr, "heap: init\n");
    head = calloc(1, sizeof(heap_t));
    if (!head) { fprintf(stderr, "heap: init failed\n"); return; }
    return;
}

void heap_check(void) {
    if (!head) { fprintf(stderr, "heap: not init\n"); return; }
    heap_t *tmp = head; head = head->next; free(tmp);
    while (head) {
        heap_warn(head->file, head->line, head->ptr, head->size, "memory leak");
        tmp = head; head = head->next; free(tmp->ptr); free(tmp);
    }
    fprintf(stderr, "heap: check\n");
    return;
}

void *heap_malloc(const char *file, size_t line, size_t size) {
    if (!head) return malloc(size);
    if (!size) { heap_warn(file, line, NULL, 0, "size is zero"); return NULL; }
    void *ptr = malloc(size);
    if (!ptr) { heap_warn(file, line, NULL, size, "malloc failed"); return NULL; }
    heap_push(file, line, ptr, size);
    return ptr;
}

void *heap_calloc(const char *file, size_t line, size_t n, size_t size) {
    if (!head) return calloc(n, size);
    if (!n || !size) { heap_warn(file, line, NULL, 0, "size is zero"); return NULL; }
    void *ptr = calloc(n, size);
    if (!ptr) { heap_warn(file, line, NULL, n * size, "calloc failed"); return NULL; }
    heap_push(file, line, ptr, n * size);
    return ptr;
}

void *heap_realloc(const char *file, size_t line, void *ptr, size_t size) {
    if (!head) return realloc(ptr, size);
    if (!size) { heap_warn(file, line, NULL, 0, "size is zero"); return NULL; }
    heap_delete(ptr);
    ptr = realloc(ptr, size);
    if (!ptr) { heap_warn(file, line, NULL, size, "realloc failed"); return NULL; }
    heap_push(file, line, ptr, size);
    return NULL;
}

void heap_free(const char *file, size_t line, void *ptr) {
    if (!head) { free(ptr); return; }
    heap_delete(ptr);
    free(ptr);
    return;
}
