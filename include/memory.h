#ifndef __MEMORY_H
#define __MEMORY_H

#include <types.h>

void *memcpy(void *source, void *dest, size length);
void *memmove(void *source, void *dest, size length);
void *memset(void *source, byte to, size length);
int memcmp(void *a, void *b, size length);
void *memchr(void *source, byte target, size length);

#endif