#include <stdio.h>
#include <stdlib.h>

#include "heapcheck.h"

heapcheck *head, *tail;

void heapcheck_init(void) {
    tail = head = calloc(1, sizeof(heapcheck));
    return;
}

void heapcheck_check(void) {
    for (heapcheck *mem = head->next; mem; mem = mem->next) {
        fprintf(stderr, "heapcheck: heap not freed [file: %s, line: %d, address: %p, size: %zu]\n", mem->file, mem->line, mem->ptr, mem->size);
    }

    return;
}

void *heapcheck_malloc(const char *file, int line, size_t size) {
    void *ptr = malloc(size);

    if (!ptr) {
        return NULL;
    }

    tail = tail->next = calloc(1, sizeof(heapcheck));
    tail->ptr = ptr;
    tail->file = file;
    tail->line = line;
    tail->size = size;
    return ptr;
}

void *heapcheck_calloc(const char *file, int line, size_t n, size_t size) {
    void *ptr = calloc(n, size);

    if (!ptr) {
        return NULL;
    }

    tail = tail->next = calloc(1, sizeof(heapcheck));
    tail->ptr = ptr;
    tail->file = file;
    tail->line = line;
    tail->size = n * size;
    return ptr;
}

void *heapcheck_realloc(const char *file, int line, void *ptr, size_t size) {
    for (heapcheck *mem = head->next; mem; mem = mem->next) {
        if (mem->ptr == ptr) {
            void *new = realloc(ptr, size);

            if (!new) {
                return NULL;
            }

            mem->ptr = new;
            mem->file = file;
            mem->line = line;
            mem->size = size;
            return new;
        }
    }

    fprintf(stderr, "heapcheck: heap not found [file: %s, line: %d, address: %p, size: %zu]\n", file, line, ptr, size);
    return NULL;
}

void heapcheck_free(const char *file, int line, void *ptr) {
    for (heapcheck *mem = head; mem->next; mem = mem->next) {
        if (mem->next->ptr == ptr) {
            heapcheck *del = mem->next;
            mem->next = mem->next->next;
            free(del);
            free(ptr);
            return;
        }
    }

    fprintf(stderr, "heapcheck: heap not found [file: %s, line: %d, address: %p, size: %zu]\n", file, line, ptr, 0);
    return;
}
