#include "internal.h"
#include <malloc.h>
#include <memory.h>

void *realloc(void *ptr, size len) {
    if (!ptr) return malloc(len);
    if (len == 0) {
        free(ptr);
        return NULL;
    }

    malloc_header *header = __malloc_get_header(ptr);
    size aligned_len = __malloc_align_up(len);

    if (header->size >= aligned_len) {
        __malloc_split(header, aligned_len);
        return ptr;
    }

    if (header->next && header->next->is_free && (header->size + HEADER_SIZE + header->next->size) >= aligned_len) {
        header->size = HEADER_SIZE + header->next->size;
        malloc_header *old_next = header->next;
        header->next = old_next->next;
        if (header->next) header->next->prev = header;

        __malloc_split(header, aligned_len);
        return ptr;
    }

    void *new_ptr = malloc(len);
    if (!new_ptr) return NULL;

    memcpy(new_ptr, ptr, header->size);
    free(ptr);
    return new_ptr;
}