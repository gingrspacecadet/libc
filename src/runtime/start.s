global _start
extern main
extern exit

section .text
_start:
    mov rdi, [rsp]      ; argc
    mov rsi, [rsp + 8]  ; argv
    mov rdx, [rsp + 16] ; environ
    and rsp, -16        ; realign the stack
    
    call main
    
    ; sys_exit with code returned from main
    mov rdi, rax
    call exit