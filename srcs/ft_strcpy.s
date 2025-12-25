global ft_strcpy

section .text

ft_strcpy:
    mov rax, rdi        ; devolver dst
.copy:
    mov dl, [rsi]       ; cargar byte de src
    mov [rdi], dl       ; copiar a dst
    inc rdi
    inc rsi
    test dl, dl         ; ¿era '\0'?
    jne .copy
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
