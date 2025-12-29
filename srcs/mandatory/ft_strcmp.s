global ft_strcmp

section .text

ft_strcmp:
.loop:
    movzx eax, byte [rdi]
    movzx edx, byte [rsi]
    cmp al, dl
    jne .diff
    test al, al
    je .equal
    inc rdi
    inc rsi
    jmp .loop

.diff:
    sub eax, edx
    ret

.equal:
    xor eax, eax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
