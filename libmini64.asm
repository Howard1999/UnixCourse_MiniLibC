
%macro gensys 2
    global sys_%2: function

sys_%2:
    push r10
    mov r10, rcx
    mov rax, %1
    syscall
    pop r10
    ret
%endmacro

    section .data
    section .text

    gensys  1, write
    gensys 60, exit