#include <cstring.h>

size cstring_length(cstring str) {
    size i = 0;
    while (*str++) i++;
    return i;
}