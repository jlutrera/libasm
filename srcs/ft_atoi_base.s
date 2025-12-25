global ft_atoi_base

section .text

; -----------------------------------------
; int ft_atoi_base(char *str, char *base)
; rdi = str
; rsi = base
; -----------------------------------------

ft_atoi_base:
    ; validar base
    push rdi
    push rsi
    call validate_base
    cmp rax, 0
    je .invalid
    mov r12, rax        ; base_len

    pop rsi
    pop rdi

    ; saltar espacios
.skip_spaces:
    mov al, [rdi]
    cmp al, ' '
    je .inc
    cmp al, 9
    jb .done_skip
    cmp al, 13
    ja .done_skip
.inc:
    inc rdi
    jmp .skip_spaces
.done_skip:

    ; signo
    mov rbx, 1
    mov al, [rdi]
    cmp al, '-'
    jne .check_plus
    mov rbx, -1
    inc rdi
    jmp .convert
.check_plus:
    cmp al, '+'
    jne .convert
    inc rdi

.convert:
    xor rax, rax        ; resultado
.loop:
    mov dl, [rdi]
    test dl, dl
    je .end

    mov rdi, rsi
    mov rcx, r12
    call index_in_base
    cmp rax, -1
    je .end

    mov rdx, r12
    imul rax, rdx
    add rax, rdx
    inc rdi
    jmp .loop

.end:
    imul rax, rbx
    ret

.invalid:
    xor rax, rax
    ret

; -----------------------------------------
; validar base: devuelve longitud o 0
; -----------------------------------------
validate_base:
    mov rdi, rsi
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
    inc rcx
    jmp .len_loop

.check_len:
    cmp rcx, 2
    jb .fail

    ; duplicados
    mov rdx, 0
.outer:
    cmp rdx, rcx
    jge .ok
    mov r8b, [rsi + rdx]
    mov r9, rdx
    inc r9
.inner:
    cmp r9, rcx
    jge .next
    cmp r8b, [rsi + r9]
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

; -----------------------------------------
; index_in_base(char c, char *base, len)
; rdi = base
; rcx = len
; dl = char
; -----------------------------------------
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
