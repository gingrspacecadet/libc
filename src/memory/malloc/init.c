#include <syscall.h>
#include <types.h>
#include "internal.h"

void *__heap_addr = NULL;
size __heap_cap = 0;

#define HEAP_MAP_HINT   (void*)0x4000000000ULL

void __heap_init(void) {
    if (__heap_addr) return;

    __heap_addr = mmap(HEAP_MAP_HINT, HEAP_SIZE, 0x1 | 0x2, 0x20 | 0x2, -1, 0);
    __heap_cap = HEAP_SIZE;

    malloc_header *first = (malloc_header*)__heap_addr;
    first->size = HEAP_SIZE - HEADER_SIZE;
    first->is_free = true;
    first->next = NULL;
    first->prev = NULL;

    __malloc_free_list = first;
}