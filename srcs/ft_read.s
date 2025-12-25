global ft_read
extern __errno_location

section .text

ft_read:
    mov rax, 0       ; syscall read
    syscall
    cmp rax, 0
    jge .ok

    mov rdi, rax
    neg rdi

    call __errno_location
    mov [rax], edi

    mov rax, -1
.ok:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
