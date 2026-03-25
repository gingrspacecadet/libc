global _start
extern main

section .text
_start:
    ; setup argc, argv and realign stack
    mov rdi, [rsp]
    mov rsi, [rsp + 8]
    and rsp, -16
    
    call main
    
    ; sys_exit with code returned from main
    mov rdi, rax
    mov rax, 60
    syscall