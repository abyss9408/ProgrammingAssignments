; ------------------------------------------------------------------
; File: functions.asm
; Project: CSD1100 Assignment 11
; Author: Vadim Surov, vsurov@digipen.edu
; Co-Author: Bryan Ang Wei Ze, bryanweize.ang@digipen.edu
;
; Compile: nasm -f elf64 -g -F dwarf functions.asm -o functions.o
; Link: gcc main.o functions.o -o main.o -lm
; Run: ./main 0
; Debug: gdb main
;  (gdb) b f1
;  (gdb) run
;  ...
;  0
;  ...
;  (gdb) ...
;
; Copyright: 2021, Digipen Institute of Technology, Singapore
;
; Note: All functions use at most 6 parameters
;      p1, p2, p3, p4, p5, p6
;      located in registers
;      rdi, rsi, rdx, rcx, r8, r9
;      accordingly.
; ------------------------------------------------------------------

    section .text

    global f1
    global f2

f1:
    mov rax, rdi
    sub rax, rdx
    imul rax
    mov r11, rax

    xor rdx, rdx
    mov rax, rsi
    sub rax, rcx
    imul rax
    mov r12, rax

    add r11, r12

    xor rdx, rdx
    mov rax, r8
    add rax, r9
    imul rax

    cmp r11, rax
    jle intersecting    ; return 1 if both circles intersect, else 0

    mov rax, 0
    ret    ; return rax;

intersecting:
    mov rax, 1
    ret    ; return rax;

f2:
    mov rcx, rdx
    add rcx, 1      ; iterations is p3 + 1
    xor r15, r15    ; use r15 to store result
    add rsi, rdx    ; add p3 to p2
    mov r14, rdx    ; use r14 to hold original value of rdx

repeat:
    push rcx
    mov rax, rdi
    add rax, r14

    imul rsi

    add r15, rax

    dec r14
    dec rsi

    pop rcx
    loop repeat

    mov rax, r15    ; move the result to rax
    ret    ; return rax;