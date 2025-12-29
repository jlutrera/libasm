global ft_list_sort
extern ft_strcmp

section .text

; void ft_list_sort(t_list **begin_list, int (*cmp)())

ft_list_sort:
    mov rbx, rdi        ; **begin_list
    mov r12, rsi        ; cmp

.outer:
    mov rdi, [rbx]
    test rdi, rdi
    je .end

    mov r13, rdi
.inner:
    mov r14, [r13 + 8]
    test r14, r14
    je .next_outer

    mov rdi, [r13]      ; data1
    mov rsi, [r14]      ; data2
    call r12
    cmp rax, 0
    jle .no_swap

    ; swap data
    mov rdx, [r13]
    mov rcx, [r14]
    mov [r13], rcx
    mov [r14], rdx

.no_swap:
    mov r13, r14
    jmp .inner

.next_outer:
    jmp .outer

.end:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
