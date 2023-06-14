#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "heapcheck.h"

static bool flag = false;
static heapcheck *head, *tail;

static void heapcheck_immediate(const char *file, int line, void *ptr, size_t size, heapcheck *mem) {
    mem->file = file;
    mem->line = line;
    mem->ptr = ptr;
    mem->size = size;
    return;
}

static void heapcheck_waening(const char *file, int line, void *ptr, size_t size, const char *msg) {
    fprintf(stderr, "heapcheck: %s [file: %s, line: %d, address: %p, size: %zu]\n", msg, file, line, ptr, size);
    return;
}

void heapcheck_init(void) {
    flag = true;
    tail = head = calloc(1, sizeof(heapcheck));

    if (!head) {
        fprintf(stderr, "heapcheck: init failed\n");
        return;
    }

    return;
}

void heapcheck_check(void) {
    if (!flag) {
        fprintf(stderr, "heapcheck: not initialized\n");
        return;
    }

    for (heapcheck *mem = head->next; mem; mem = mem->next) {
        heapcheck_waening(mem->file, mem->line, mem->ptr, mem->size, "memory leak");
    }

    return;
}

void *heapcheck_malloc(const char *file, int line, size_t size) {
    if (!flag) {
        return malloc(size);
    }

    if (!size) {
        heapcheck_waening(file, line, NULL, size, "size is zero");
        return NULL;
    }

    void *ptr = malloc(size);

    if (!ptr) {
        heapcheck_waening(file, line, ptr, size, "malloc failed");
        return ptr;
    }

    tail = tail->next = calloc(1, sizeof(heapcheck));
    heapcheck_immediate(file, line, ptr, size, tail);
    return ptr;
}

void *heapcheck_calloc(const char *file, int line, size_t n, size_t size) {
    if (!flag) {
        return calloc(n, size);
    }

    if (!n || !size) {
        heapcheck_waening(file, line, NULL, n * size, "size is zero");
        return NULL;
    }

    void *ptr = calloc(n, size);

    if (!ptr) {
        heapcheck_waening(file, line, ptr, n * size, "calloc failed");
        return ptr;
    }

    tail = tail->next = calloc(1, sizeof(heapcheck));
    heapcheck_immediate(file, line, ptr, n * size, tail);
    return ptr;
}

void *heapcheck_realloc(const char *file, int line, void *ptr, size_t size) {
    if (!flag) {
        return realloc(ptr, size);
    }

    if (!size) {
        heapcheck_waening(file, line, NULL, size, "size is zero");
        return NULL;
    }

    for (heapcheck *mem = head->next; mem; mem = mem->next) {
        if (mem->ptr == ptr) {
            void *new = realloc(ptr, size);

            if (!new) {
                heapcheck_waening(file, line, mem->ptr, mem->size, "realloc failed");
                heapcheck_waening(file, line, new, size, "realloc failed");
                return new;
            }

            heapcheck_immediate(file, line, new, size, mem);
            return new;
        }
    }

    heapcheck_waening(file, line, ptr, 0, "heap not found");
    return NULL;
}

void heapcheck_free(const char *file, int line, void *ptr) {
    if (!flag) {
        return free(ptr);
    }

    for (heapcheck *mem = head; mem->next; mem = mem->next) {
        if (mem->next->ptr == ptr) {
            heapcheck *del = mem->next;
            mem->next = mem->next->next;
            free(del);
            free(ptr);
            return;
        }
    }

    heapcheck_waening(file, line, ptr, 0, "heap not found");
    return;
}
