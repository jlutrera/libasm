global ft_write
extern __errno_location

section .text

ft_write:
    mov     rax, 1          ; syscall write
    syscall

    cmp     rax, 0
    jge     .ok             ; si rax >= 0 → éxito

    ; error: rax = -errno
    neg     rax             ; rax = errno positivo
    mov     rdi, rax        ; rdi = errno
    call    __errno_location  ; rax = &errno
    mov     [rax], rdi      ; *errno = errno
    mov     rax, -1         ; return -1
    ret

.ok:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
