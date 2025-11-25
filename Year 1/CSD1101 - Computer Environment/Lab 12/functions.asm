; ------------------------------------------------------------------
; File: functions.asm
; Project: CSD1100 Assignment 12
; Author: Vadim Surov, vsurov@digipen.edu
; Co-Author: Bryan Ang Wei Ze, bryanweize.ang@digipen.edu
;
; Compile: nasm -f elf64 -g -F dwarf functions.asm -o functions.o
; Link: gcc main.o functions.o -o main.o -lm
; Run: ./main 0
; Debug: gdb main
;  (gdb) b len
;  (gdb) run
;  0
;  ...
;  To see a string in memory by address in rdi use gdb's command:
;  (gdb) p/d (char[20]) *$rdi
;   ...
;
; Copyright: 2021, Digipen Institute of Technology, Singapore
;
; Note: All functions use at most 6 parameters
;      p1, p2, p3, p4, p5, p6
;      located in registers
;      rdi, rsi, rdx, rcx, r8, r9
;      accordingly.
; Note 2: Use instruction cmp byte [rdi+rcx], 0 to campare
;         a byte by adddress rdi*rci with 0
; ------------------------------------------------------------------
    section .text

    global len
    global countn
    global counta
    global counts

len:
    xor rcx, rcx    ; use rcx for offset
    xor rax, rax  ; use rax for counter
    jmp check_if_null

not_null:
    inc rax
    inc rcx

check_if_null:
    cmp byte [rdi+rcx], 0
    jnz not_null
    ret    ; return rax



countn:
    call len
    xor rcx, rcx    ; use rcx for offset
    xor r9, r9  ; use r9 for non digit counter
    cmp byte [rdi+rcx], 0
    jnz countn_ifn
    jmp endn    ; string is empty

notn:
    inc r9
    jmp next_charn

countn_ifn:
    cmp byte [rdi+rcx], 57
    jg notn ; ASCII values greater than 57
    cmp byte [rdi+rcx], 48
    jl notn ; and less than 48 are not digits

next_charn:
    inc rcx
    cmp byte [rdi+rcx], 0
    jnz countn_ifn

endn:
    sub rax, r9    ; subtract non-digits from string length
    ret    ; return rax



counta:
    call len
    xor rcx, rcx    ; use rcx for offset
    xor r9, r9  ; use r9 for non digit counter
    cmp byte [rdi+rcx], 0 ; check if char is not null
    jnz counta_ifa
    jmp enda    ; string is empty

nota:
    inc r9
    jmp next_chara

counta_ifa: ; if ASCII value is less than 65 or more than 122 as well as between 91 and 96, !alphabet_letter
    cmp byte [rdi+rcx], 122
    jg nota

    cmp byte [rdi+rcx], 65
    jl nota

    cmp byte [rdi+rcx], 90
    jle next_chara

    cmp byte [rdi+rcx], 97
    jl nota

next_chara:
    inc rcx
    cmp byte [rdi+rcx], 0
    jnz counta_ifa

enda:
    sub rax, r9    ; subtract non-alphabets from string length
    ret    ; return rax



counts:
    call len
    mov r10, rax    ; use r10 to store string length

    call countn
    mov r11, rax    ; use r11 to store digit count

    call counta
    mov r12, rax    ; use r12 to store alphabet count

    sub r10, r11    ; subtract digits and alphabets from string length
    sub r10, r12
    mov rax, r10
    ret    ; return rax