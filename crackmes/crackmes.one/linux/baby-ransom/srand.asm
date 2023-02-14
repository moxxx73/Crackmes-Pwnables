; this code (with some additions/changes) is ripped straight
; from the disassembly so i could maintain precision
global _start
extern srand
extern rand
extern printf

section .text

_start:
    sub rsp, 8
        
    mov edi, 0xdeadbeef
    call srand
    call rand
    mov edx, eax
    movsxd rax, edx
    imul rax, rax, 0xffffffff80808081
    
    shr rax, 0x20
    add eax, edx
    sar eax, 7
    
    mov ecx, eax
    mov eax, edx
    sar eax, 0x1f

    sub ecx, eax
    mov eax, ecx
    mov [rsp], eax

    mov ecx, [rsp]
    mov eax, ecx
    shl eax, 8
    sub eax, ecx
    
    sub edx, eax
    mov eax, edx
    mov [rsp], eax
    xor rax, rax

    mov rdi, result_out
    xor rsi, rsi
    mov sil, byte [rsp]
    call printf

    xor rdi, rdi
    mov rax, 0x3c
    syscall

section .data
srand_out:  db  "calling srand(0x%x)", 10, 0
result_out: db  "Result: 0x%x", 10, 0