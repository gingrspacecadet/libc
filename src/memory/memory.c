#include <memory.h>

void *memcpy(void *source, void *dest, size length) {
    if (!source || !dest) return NULL;
    if (length < 1) return NULL;
    for (size i = 0; i < length; i++) {
        ((char*)dest)[i] = ((char*)source)[i];
    }
    return dest;
}

void *memmove(void *source, void *dest, size length) {
    if (!source || !dest || length < 1) return NULL;
    char tmp[length];
    memcpy(source, tmp, length);
    memcpy(tmp, dest, length);
    return dest;
}

void *memset(void *source, byte to, size length) {
    if (!source || length < 1) return NULL;
    for (size i = 0; i < length; i++) {
        ((char*)source)[i] = to;
    }
    return source;
}

int memcmp(void *a, void *b, size length) {
    if (!a || !b || length < 1) return -1;
    for (size i = 0; i < length; i++) {
        if (((char*)a)[i] != ((char*)b)[i]) {
            return ((char*)a)[i] - ((char*)b)[i];
        }
    }
    return -1;
}

void *memchr(void *source, byte target, size length) {
    if (!source || length < 1) return NULL;
    for (size i = 0; i < length; i++) {
        if (((char*)source)[i] == target) {
            return &((char*)source)[i];
        }
    }
    return NULL;
}