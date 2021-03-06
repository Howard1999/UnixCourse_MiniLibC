
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

    gensys   1, write
    gensys  13, rt_sigaction
    gensys  14, rt_sigprocmask
    gensys  34, pause
    gensys  35, nanosleep
    gensys  37, alarm
    gensys  60, exit
    gensys 127, rt_sigpending

    global sys_rt_sigreturn: function
sys_rt_sigreturn:
    mov rax, 15
    syscall

    global setjmp: function
setjmp:
    ; ptr size = 8 byte
    ; rdi: env ptr

    ; save regster
    mov     QWORD [rdi], rbx
    mov     QWORD [rdi+ 8], rsp
    mov     QWORD [rdi+16], rbp
    mov     QWORD [rdi+24], r12
    mov     QWORD [rdi+32], r13
    mov     QWORD [rdi+40], r14
    mov     QWORD [rdi+48], r15
    ; save return address
    mov     rax, [rsp]          ; load return address to rax
    mov     QWORD [rdi+56], rax ; save into env[0].reg[7]
    ; save signal mask
    push    rdi                 ; backup rdi
    push    rax                 ; allocate 8 byte in stack

    mov     rdi, 0              ; sys_rt_sigprocmask(SIG_BLOCK, NULL, rsp, 8)
    mov     rsi, 0              ;
    mov     rdx, rsp            ;
    mov     rcx, 8              ;
    call    sys_rt_sigprocmask  ;

    pop     rax                 ; release allocated stack
    pop     rdi                 ; recover rdi
    mov     QWORD [rdi+64], rax ; put sigmask to env[0].mask
    ; return = 0
    mov     rax, 0 

    ret

    global longjmp: function
longjmp:
    ; rdi: env ptr
    ; rsi: val

    ; load regster
    mov     rbx, QWORD [rdi]
    mov     rsp, QWORD [rdi+ 8]
    mov     rbp, QWORD [rdi+16]
    mov     r12, QWORD [rdi+24]
    mov     r13, QWORD [rdi+32]
    mov     r14, QWORD [rdi+40]
    mov     r15, QWORD [rdi+48]
    ; load return address
    mov     rax, QWORD [rdi+56] ; load saved return address to rax
    mov     [rsp], rax          ; setup return address
    ; recover sigmask
    mov     rsi, rdi            ; rsi(second pram) = &env[0].mask
    add     rsi, 64             ; 
    mov     rdi, 2              ; sys_rt_sigprocmask(SIG_SETMASK, &env[0].mask, NULL, 8)
    mov     rdx, 0              ;
    mov     rcx, 8              ;
    call    sys_rt_sigprocmask  ; 
    ; return = val
    mov     rax, rsi
    
    ret
