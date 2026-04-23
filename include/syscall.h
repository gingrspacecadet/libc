#ifndef __SYSCALL_H
#define __SYSCALL_H

#define SYS_READ    0
#define SYS_WRITE   1
#define SYS_OPEN    2
#define SYS_CLOSE   3
#define SYS_STAT    4
#define SYS_FSTAT   5
#define SYS_LSTAT   6
#define SYS_POLL    7
#define SYS_LSEEK   8
#define SYS_MMAP    9
#define SYS_MPROTECT    10
#define SYS_MUNMAP  11
#define SYS_BRK     12
#define SYS_RT_SIGACTION    13
#define SYS_RT_SIGPROCMASK  14
#define SYS_RT_SIGRETURN    15
#define SYS_IOCTL   16
#define SYS_PREAD64 17
#define SYS_PWRITE64    18
#define SYS_READV   19
#define SYS_WRITEV  20
#define SYS_ACCESS  21
#define SYS_PIPE    22
#define SYS_SELECT  23
#define SYS_SCHED_YIELD 24
#define SYS_MREMAP  25
#define SYS_MSYNC   26
#define SYS_MINCORE 27
#define SYS_MADVICE 28
#define SYS_SHMGET  29
#define SYS_SHMAT   30
#define SYS_SHMCTL  31
#define SYS_DUP 32
#define SYS_DUP2    33
#define SYS_PAUSE   34
#define SYS_NANOSLEEP   35
#define SYS_GETITIMER   36
#define SYS_ALARM   37
#define SYS_SETITIMER   38
#define SYS_GETPID  39
#define SYS_SENDFILE    40
#define SYS_SOCKET  41
#define SYS_CONNECT  42
#define SYS_ACCEPT  43
#define SYS_SENDTO  44
#define SYS_RECVFROM    45
#define SYS_SENDMSG 46
#define SYS_RECVMSG 47
#define SYS_SHUTDOWN    48
#define SYS_BIND    49
#define SYS_LISTEN  50
#define SYS_GETSOCKNAME 51
#define SYS_GETPEERNAME 52
#define SYS_SOCKETPAIR  53
#define SYS_SETSOCKOPT  54
#define SYS_GETSOCKOPT  55
#define SYS_CLONE   56
#define SYS_FORK    57
#define SYS_VFORK   58
#define SYS_EXECVE  59
#define SYS_EXIT    60

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
