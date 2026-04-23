#include <lib.h>
#include <syscall.h>
#include <atexit.h>

__attribute__((noreturn)) void exit(int code) {
    __syscall1(SYS_EXIT, code);
    __builtin_unreachable();
}