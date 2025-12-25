global ft_write
extern __errno_location

section .text

ft_write:
    mov rax, 1       ; syscall write
    syscall
    cmp rax, 0
    jge .ok          ; si rax >= 0 → OK

    ; error → setear errno
    mov rdi, rax     ; guardar código de error negativo
    neg rdi          ; convertirlo a positivo

    call __errno_location
    mov [rax], edi   ; *errno = error

    mov rax, -1
.ok:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
