#include <cstring.h>
#include <malloc.h>

size cstring_length(cstring str) {
    size i = 0;
    while (*str++) i++;
    return i;
}

void cstring_append(cstring *dest, cstring src) {
    if (!dest || !*dest || !src) {
        return;
    }
    size dest_len = cstring_length(*dest);
    size src_len = cstring_length(src);
    size new_len = dest_len + src_len;

    char *new_str = malloc(new_len + 1);
    if (*dest) {
        for (size i = 0; i < dest_len; i++) {
            new_str[i] = (*dest)[i];
        }
    }
    for (size i = 0; i < src_len; i++) {
        new_str[dest_len + i] = src[i];
    }
    new_str[new_len] = '\0';

    free(*dest);
    *dest = new_str;
}