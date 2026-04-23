#include "internal.h"

void free(void *ptr) {
    if (!ptr) return;

    malloc_header *header = __malloc_get_header(ptr);
    header->is_free = true;
    __malloc_coalesce(header);
}