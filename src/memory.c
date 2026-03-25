#include <memory.h>

void memcpy(void *dst, const void *src, size len) {
    for (size i = 0; i < len; i++) {
        ((char *)dst)[i] = ((const char *)src)[i];
    }
}