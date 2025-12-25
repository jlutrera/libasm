global ft_list_size

section .text

; int ft_list_size(t_list *begin_list)

ft_list_size:
    xor rax, rax
.loop:
    test rdi, rdi
    je .end
    inc rax
    mov rdi, [rdi + 8] ; next
    jmp .loop
.end:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
