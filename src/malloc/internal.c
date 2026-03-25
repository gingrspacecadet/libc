#include "internal.h"

malloc_header *__malloc_free_list = NULL;

malloc_header *__malloc_find_free(size length) {
    malloc_header *curr = __malloc_free_list;
    while (curr) {
        if (curr->is_free && curr->size >= length) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void __malloc_split(malloc_header *header, size aligned_len) {
    if (header->size >= aligned_len + HEADER_SIZE + MIN_ALLOC_SIZE) {
        malloc_header *new_block = (malloc_header*)((char*)header + HEADER_SIZE + aligned_len);
        new_block->size = header->size - aligned_len - HEADER_SIZE;
        new_block->is_free = true;
        new_block->next = header->next;
        new_block->prev = header;

        if (header->next) header->next->prev = new_block;
        header->next = new_block;
        header->size = aligned_len;
    }
}

void __malloc_coalesce(malloc_header *header) {
    if (!header || !header->is_free) return;

    if (header->next && header->next->is_free) {
        header->size += HEADER_SIZE + header->next->size;
        malloc_header *old_next = header->next;
        header->next = old_next->next;
        if (header->next) header->next->prev = header;
    }

    if (header->prev && header->prev->is_free) {
        malloc_header *prev = header->prev;
        prev->size += HEADER_SIZE + header->size;
        prev->next = header->next;
        if (header->next) header->prev->next = prev;
    }
}