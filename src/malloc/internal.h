#ifndef __MALLOC_INTERNAL_H
#define __MALLOC_INTERNAL_H

#include <types.h>
#include <syscall.h>

typedef struct malloc_header {
    size size;
    bool is_free;
    struct malloc_header *next;
    struct malloc_header *prev;
} malloc_header;

#define MIN_ALLOC_SIZE 16
#define HEADER_SIZE sizeof(malloc_header)
#define HEAP_SIZE 1048576

extern malloc_header *__malloc_free_list;

static inline size __malloc_align_up(size s) {
    return (s + 15) & ~15;
}

static inline malloc_header *__malloc_get_header(void *ptr) {
    return (malloc_header*)((char*)ptr - HEADER_SIZE);
}

malloc_header *__malloc_find_free(size len);
void __malloc_split(malloc_header *header, size aligned_len);
void __malloc_coalesce(malloc_header *header);

extern void *__heap_addr;
extern size __heap_cap;
void __heap_init(void);

static inline void *mmap(void *addr, size len, int prot, int flags, int fd, int offset) {
   return (void*) __syscall6(9, (long)addr, len, prot, flags, fd, offset);
}

#endif