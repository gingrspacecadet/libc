#include <io.h>
#include <syscall.h>

int io_print_string(string str) {
    return __syscall3(SYS_WRITE, STDOUT, (long)str.data, str.length);
}

int io_print_cstring(cstring str) {
    return __syscall3(SYS_WRITE, STDOUT, (long)str, cstring_length(str));
}

int io_print_hexulong(hexulong num) {
    char buffer[17]; // 16 hex digits + null terminator
    for (int i = 0; i < 16; i++) {
        int digit = (num >> ((15 - i) * 4)) & 0xF;
        buffer[i] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
    }
    buffer[16] = '\0';
    return io_print_cstring(buffer);
}