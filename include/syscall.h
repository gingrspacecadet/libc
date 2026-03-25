#ifndef __SYSCALL_H
#define __SYSCALL_H

#define SYS_WRITE   1
#define STDOUT      1

static inline long __syscall(long n, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6) {
    long ret;
    register long r10 asm("r10") = arg4;
    register long r8 asm("r8") = arg5;
    register long r9 asm("r9") = arg6;
    __asm__ volatile (
        "syscall"
        : "=a"(ret)
        : "a"(n), "D"(arg1), "S"(arg2), "d"(arg3), "r"(r10), "r"(r8), "r"(r9)
        : "rcx", "r11", "memory"
    );

    return ret;
}

static inline long __syscall1(long n, long arg1) {
    return __syscall(n, arg1, 0, 0, 0, 0, 0);
}

static inline long __syscall2(long n, long arg1, long arg2) {
    return __syscall(n, arg1, arg2, 0, 0, 0, 0);
}

static inline long __syscall3(long n, long arg1, long arg2, long arg3) {
    return __syscall(n, arg1, arg2, arg3, 0, 0, 0);
}

static inline long __syscall4(long n, long arg1, long arg2, long arg3, long arg4) {
    return __syscall(n, arg1, arg2, arg3, arg4, 0, 0);
}

static inline long __syscall5(long n, long arg1, long arg2, long arg3, long arg4, long arg5) {
    return __syscall(n, arg1, arg2, arg3, arg4, arg5, 0);
}

static inline long __syscall6(long n, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6) {
    return __syscall(n, arg1, arg2, arg3, arg4, arg5, arg6);
}

#endif