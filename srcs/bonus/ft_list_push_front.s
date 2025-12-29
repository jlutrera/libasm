global ft_list_push_front

section .text

; void ft_list_push_front(t_list **begin_list, void *data)

ft_list_push_front:
    mov rax, rdi        ; rax = &begin_list
    mov rdi, 16         ; sizeof(t_list)
    extern malloc
    call malloc
    test rax, rax
    je .end

    mov [rax], rsi      ; new->data = data
    mov rdx, [rdi]      ; old head
    mov [rax + 8], rdx  ; new->next = old head
    mov [rdi], rax      ; *begin_list = new
.end:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
