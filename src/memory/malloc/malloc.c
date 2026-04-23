#include <memory.h>
#include "internal.h"

void *malloc(size len) {
    if (len == 0) return NULL;

    size aligned_len = __malloc_align_up(len);

    if (!__heap_addr) __heap_init();

    malloc_header *header = __malloc_find_free(aligned_len);

    if (!header) return NULL;
    
    header->is_free = false;
    __malloc_split(header, aligned_len);

    return (void*)((char*)header + HEADER_SIZE);
}

void *calloc(size len) {
    void *ptr = malloc(len);
    if (ptr) memset(ptr, 0, len);
    return ptr;
}