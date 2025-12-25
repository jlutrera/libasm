global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

section .text

ft_strdup:
    test rdi, rdi
    je .null

    ; len = ft_strlen(s)
    mov rdi, rdi
    call ft_strlen

    inc rax              ; espacio para '\0'
    mov rdi, rax
    call malloc
    test rax, rax
    je .null

    mov rdi, rax         ; dst
    mov rsi, rdx         ; src original
    call ft_strcpy
    ret

.null:
    xor rax, rax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
