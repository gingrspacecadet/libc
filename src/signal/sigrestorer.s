section .text
global __rt_sigreturn_stub

__rt_sigreturn_stub:
    mov rax, 15
    syscall