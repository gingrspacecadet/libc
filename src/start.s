global _start
extern main
extern setup_alt_stack
extern setup_signal_handlers

section .text
_start:
    ; setup argc, argv and realign stack
    mov rdi, [rsp]
    mov rsi, [rsp + 8]
    and rsp, -16

    call setup_alt_stack
    call setup_signal_handlers
    
    call main
    
    ; sys_exit with code returned from main
    mov rdi, rax
    mov rax, 60
    syscall