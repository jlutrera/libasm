global ft_list_remove_if
extern free

section .text

; void ft_list_remove_if(t_list **begin, void *data_ref, cmp, free_fct)

ft_list_remove_if:
    mov rbx, rdi        ; **begin
    mov r12, rsi        ; data_ref
    mov r13, rdx        ; cmp
    mov r14, rcx        ; free_fct

    mov rdi, [rbx]      ; current
    xor r15, r15        ; prev = NULL

.loop:
    test rdi, rdi
    je .end

    mov rsi, r12
    mov rax, [rdi]
    mov rdi, rax
    call r13
    cmp rax, 0
    jne .next

    ; eliminar nodo
    mov rax, [rdi + 8]  ; next
    test r15, r15
    je .update_head
    mov [r15 + 8], rax
    jmp .free_node

.update_head:
    mov [rbx], rax

.free_node:
    mov rdi, [rdi]      ; free(data)
    call r14
    mov rdi, rax
    jmp .loop

.next:
    mov r15, rdi
    mov rdi, [rdi + 8]
    jmp .loop

.end:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
