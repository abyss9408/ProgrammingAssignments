; ------------------------------------------------------------------
; File: functions.asm
; Project: CSD1101 Assignment 10
; Author: Vadim Surov, vsurov@digipen.edu
; Co-Author: Bryan Ang Wei Ze, bryanweize.ang@digipen.edu
;
; Compile: nasm -f elf64 functions.asm -o functions.o
; Link: gcc main.o functions.o -o main.o -lm
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
    global f3
    global f4
    global f5

f1: 
    mov rax, r8
    ret

f2:
    mov rax, rdi
    add rax, rsi
    add rax, rdx
    ret

f3:
    mov rax, rdx
    xor rdx, rdx
    idiv rcx
    mov r15, rax    ; r15 = p3 / p4

    mov rax, rdi
    imul rsi    ; rax = p1 * p2

    add rax, r15    ; rax += r15
 
    inc rax    ; rax++

    ret

f4:
    push rdx
    mov rax, rdi
    imul rax, 100000
    mov r11, rax   ; r11 = p1 * 100000

    xor rax, rax
    mov rax, rsi
    imul rax, 10000
    mov r12, rax    ; r12 = p2 * 10000

    pop rdx
    xor rax, rax
    mov rax, rdx
    imul rax, 1000
    mov r13, rax    ; r13 = p3 * 1000

    xor rax, rax
    mov rax, rcx
    imul rax, 100
    mov r14, rax    ; r14 = p4 * 100

    xor rax, rax
    mov rax, r8
    imul rax, 10
    mov r15, rax    ; r15 = p5 * 10

    xor rax, rax
    mov rax, r9
    add rax, r11
    add rax, r12
    add rax, r13
    add rax, r14
    add rax, r15    ; rax = p6 + r11 + r12 + r13 + r14 + r15

    ret

f5:
; TODO: Return the result of calculation 
;       p1 / 100000 - p2 / 10000 - p3 / 1000 - p4 / 100 - p5 / 10.

    push rdx
    push rsi

    mov rax, rdi
    xor rdx, rdx
    mov rsi, 100000
    idiv rsi
    mov r11, rax    ; r11 = p1 / 100000

    pop rsi
    mov rax, rsi
    xor rdx, rdx
    mov rsi, 10000
    idiv rsi
    mov r12, rax    ; r12 = p2 / 10000

    pop rdx
    mov rax, rdx
    xor rdx, rdx
    mov rsi, 1000
    idiv rsi
    mov r13, rax    ; r13 = p3 / 1000

    mov rax, rcx
    xor rdx, rdx
    mov rsi, 100
    idiv rsi
    mov r14, rax    ; r14 = p4 / 100

    mov rax, r8
    xor rdx, rdx
    mov rsi, 10
    idiv rsi
    mov r15, rax    ; r15 = p5 / 10

    mov rax, r11
    sub rax, r12
    sub rax, r13
    sub rax, r14
    sub rax, r15    ; rax = r11 - r12 - r13 - r14 - r15

    ret