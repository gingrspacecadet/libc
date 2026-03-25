#include <memory.h>

void memcpy(char *dst, char *src, size len) {
    for (size i = 0; i < len; i++) {
        dst[i] = src[i];
    }
}