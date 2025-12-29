global ft_strcpy

section .text

ft_strcpy:
    mov rax, rdi        ; return dst
.copy:
    movsb               ; copia byte [rsi] → [rdi], incrementa ambos
    cmp byte [rdi - 1], 0
    jne .copy
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
