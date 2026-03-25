#include <io.h>
#include <syscall.h>

int io_print_string(string str) {
    return __syscall3(SYS_WRITE, STDOUT, (long)str.data, str.length);
}

int io_print_cstring(cstring str) {
    return __syscall3(SYS_WRITE, STDOUT, (long)str, cstring_length(str));
}