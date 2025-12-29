global ft_atoi_base

section .text

ft_atoi_base:
    push rbx
    push r12
    push r13
    push r14
    push r15

    mov r14, rdi        ; r14 = str
    mov r13, rsi        ; r13 = base

    ; validar base
    mov rdi, r13
    call validate_base
    test rax, rax
    jz .invalid
    mov r12, rax        ; r12 = base_len

    ; saltar espacios
    mov rdi, r14
.skip_spaces:
    mov al, [rdi]
    cmp al, 9
    jb .check_space
    cmp al, 13
    jbe .inc_str
.check_space:
    cmp al, 32
    jne .done_skip
.inc_str:
    inc rdi
    jmp .skip_spaces
.done_skip:

    ; signo
    mov rbx, 1
.sign_loop:
    mov al, [rdi]
    cmp al, '+'
    je .plus
    cmp al, '-'
    je .minus
    jmp .convert

.plus:
    inc rdi
    jmp .sign_loop

.minus:
    imul rbx, rbx, -1
    inc rdi
    jmp .sign_loop

.convert:
    xor r15, r15        ; r15 = result

.loop:
    mov dl, [rdi]
    test dl, dl
    je .finish

    ; buscar índice del dígito
    mov rsi, r13        ; base
    mov rcx, r12        ; base_len
    mov rdi, r13
    call index_in_base  ; rax = index o -1

    cmp rax, -1
    je .finish

    ; result = result * base_len + digit
    mov rdx, r15
    imul rdx, r12
    add rdx, rax
    mov r15, rdx

    inc rdi             ; AVANZAR EN LA CADENA
    jmp .loop

.finish:
    mov rax, r15
    imul rax, rbx
    jmp .cleanup

.invalid:
    xor rax, rax

.cleanup:
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    ret


; ---------------------------------------------------------
; validate_base
; ---------------------------------------------------------
validate_base:
    xor rcx, rcx
.len_loop:
    mov al, [rdi + rcx]
    test al, al
    je .check_len
    cmp al, '+'
    je .fail
    cmp al, '-'
    je .fail
    cmp al, ' '
    je .fail
    cmp al, 9
    jb .ok_char
    cmp al, 13
    jbe .fail
.ok_char:
    inc rcx
    jmp .len_loop

.check_len:
    cmp rcx, 2
    jb .fail

    mov rdx, 0
.outer:
    cmp rdx, rcx
    jge .ok
    mov r8b, [rdi + rdx]
    mov r9, rdx
    inc r9
.inner:
    cmp r9, rcx
    jge .next
    cmp r8b, [rdi + r9]
    je .fail
    inc r9
    jmp .inner
.next:
    inc rdx
    jmp .outer

.ok:
    mov rax, rcx
    ret

.fail:
    xor rax, rax
    ret


; ---------------------------------------------------------
; index_in_base
; ---------------------------------------------------------
index_in_base:
    xor rax, rax
.loop2:
    cmp rax, rcx
    jge .not_found
    cmp dl, [rdi + rax]
    je .found
    inc rax
    jmp .loop2
.found:
    ret
.not_found:
    mov rax, -1
    ret


section .note.GNU-stack noalloc noexec nowrite progbits
