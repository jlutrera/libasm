global ft_strlen

section .text

ft_strlen:
    xor rax, rax            ; contador = 0
.loop:
    cmp byte [rdi + rax], 0 ; ¿fin de string?
    je .end
    inc rax
    jmp .loop
.end:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
