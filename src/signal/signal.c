#include <syscall.h>
#include <io.h>

#define SIGSEGV 11
#define SA_SIGINFO 0x00000004
#define SA_RESTORER 0x04000000
#define SA_ONSTACK 0x08000000
#define SS_ONSTACK 0x00000001
#define MINSIGSTKSZ 16384

struct k_stack_t {
    void *ss_sp;
    int ss_flags;
    unsigned long ss_size;
};

void setup_alt_stack() {
    static char alt_stack_buffer[MINSIGSTKSZ];
    struct k_stack_t ss = {0};
    ss.ss_sp = alt_stack_buffer;
    ss.ss_size = sizeof(alt_stack_buffer);
    ss.ss_flags = 0;

    __syscall1(SYS_SIGALTSTACK, (long)&ss);
}

struct k_sigaction {
    void (*sa_sigaction)(int, void *, void *);
    unsigned long sa_flags;
    void (*sa_restorer)(void);
    unsigned long sa_mask;
};

extern void __rt_sigreturn_stub(void);

void signal_handler(int signum, void *info, void *ucontext) {
    switch (signum) {
        case SIGSEGV:
            io_print("Segmentation fault.\n");
            break;
        default:
            io_print("Received unknown signal.\n");
            break;
    }

    // die otherwise it just loops
    __syscall1(60, 127); 
}

int setup_signal_handlers() {
    struct k_sigaction sa;
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO | SA_RESTORER | SA_ONSTACK;
    sa.sa_restorer = __rt_sigreturn_stub;
    sa.sa_mask = 0;

    if (__syscall4(SYS_RT_SIGACTION, SIGSEGV, (long)&sa, 0, sizeof(unsigned long)) < 0) {
        return -1;
    }

    return 0;
}