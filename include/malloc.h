#ifndef __MALLOC_H
#define __MALLOC_H

#include <types.h>

void *malloc(size len);
void *calloc(size len);
void free(void *ptr);
void *realloc(void *ptr, size len);

#endif
