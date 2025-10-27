section .data
    msg db 'temp:, ', 0
    len equ $ - msg
    newline: db 10

section .text
    global print_temp

print_temp:
    push rbp
    mov rbp, rsp
    push r12

    mov r12, rdi

    mov rax, 1
    mov rdi, 1
    mov rsi, [rel msg]
    mov rdx, len
    syscall

    xor rcx, rcx

print_loop:
    mov al, [r12 + rcx]
    cmp al, 0
    je .done
    inc rcx
    jmp print_loop

.done:
    mov rax, 1
    mov rdi, 1
    mov rsi, r12
    mov rdx, rcx
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, [rel newline]
    mov rdx, 1
    syscall

    pop r12
    mov rsp, rbp
    pop rbp
    ret