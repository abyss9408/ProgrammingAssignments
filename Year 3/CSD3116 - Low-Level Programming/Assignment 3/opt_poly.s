	.file	"opt_poly.c"
	.text
	.p2align 4
	.globl	poly_opt
	.type	poly_opt, @function
poly_opt:
.LFB0:
	.cfi_startproc
	endbr64
	movapd	%xmm0, %xmm5
	movsd	(%rdi), %xmm6
	movq	%rdi, %rdx
	movq	%rsi, %rcx
	mulsd	%xmm0, %xmm0
	movapd	%xmm5, %xmm9
	movapd	%xmm5, %xmm13
	movapd	%xmm5, %xmm14
	mulsd	%xmm0, %xmm9
	movapd	%xmm0, %xmm8
	mulsd	%xmm0, %xmm8
	movapd	%xmm9, %xmm10
	mulsd	%xmm9, %xmm10
	movapd	%xmm8, %xmm11
	mulsd	%xmm8, %xmm13
	mulsd	%xmm8, %xmm11
	mulsd	%xmm10, %xmm14
	cmpq	$7, %rsi
	jle	.L2
	leaq	8(%rdi), %rax
	leaq	-8(%rsi), %rdi
	pxor	%xmm4, %xmm4
	movapd	%xmm5, %xmm1
	shrq	$3, %rdi
	movapd	%xmm4, %xmm7
	movapd	%xmm4, %xmm3
	movq	%rdi, %rsi
	salq	$6, %rsi
	leaq	72(%rdx,%rsi), %rsi
	.p2align 4,,10
	.p2align 3
.L3:
	movsd	24(%rax), %xmm2
	movsd	32(%rax), %xmm12
	addq	$64, %rax
	mulsd	%xmm9, %xmm2
	addsd	-64(%rax), %xmm2
	mulsd	%xmm8, %xmm12
	mulsd	%xmm1, %xmm2
	addsd	%xmm2, %xmm6
	movsd	-56(%rax), %xmm2
	mulsd	%xmm5, %xmm2
	addsd	%xmm12, %xmm2
	movsd	-24(%rax), %xmm12
	mulsd	%xmm13, %xmm12
	mulsd	%xmm1, %xmm2
	addsd	%xmm2, %xmm3
	movsd	-48(%rax), %xmm2
	mulsd	%xmm0, %xmm2
	addsd	%xmm12, %xmm2
	movsd	-8(%rax), %xmm12
	mulsd	%xmm14, %xmm12
	mulsd	%xmm1, %xmm2
	addsd	%xmm2, %xmm7
	movsd	-16(%rax), %xmm2
	mulsd	%xmm10, %xmm2
	addsd	%xmm12, %xmm2
	mulsd	%xmm1, %xmm2
	mulsd	%xmm11, %xmm1
	addsd	%xmm2, %xmm4
	cmpq	%rax, %rsi
	jne	.L3
	leaq	9(,%rdi,8), %rax
	cmpq	%rax, %rcx
	jl	.L4
	movsd	(%rdx,%rax,8), %xmm0
	leaq	0(,%rax,8), %rsi
	mulsd	%xmm1, %xmm0
.L8:
	leaq	1(%rax), %r8
	mulsd	%xmm5, %xmm1
	addsd	%xmm0, %xmm6
	cmpq	%r8, %rcx
	jl	.L4
	movsd	8(%rdx,%rsi), %xmm0
	movq	%rax, %rdi
	andl	$3, %edi
	mulsd	%xmm1, %xmm0
	cmpq	$1, %rdi
	je	.L51
	addsd	%xmm0, %xmm6
.L12:
	leaq	2(%rax), %rdi
	mulsd	%xmm5, %xmm1
	cmpq	%rdi, %rcx
	jl	.L4
	movsd	16(%rdx,%rsi), %xmm0
	andl	$3, %r8d
	mulsd	%xmm1, %xmm0
	cmpq	$2, %r8
	je	.L13
	cmpq	$3, %r8
	je	.L14
	cmpq	$1, %r8
	je	.L52
	addsd	%xmm0, %xmm6
.L17:
	leaq	3(%rax), %r8
	mulsd	%xmm5, %xmm1
	cmpq	%r8, %rcx
	jl	.L4
	movsd	24(%rdx,%rsi), %xmm0
	andl	$3, %edi
	mulsd	%xmm1, %xmm0
	cmpq	$2, %rdi
	je	.L18
	cmpq	$3, %rdi
	je	.L19
	cmpq	$1, %rdi
	je	.L53
	addsd	%xmm0, %xmm6
.L22:
	leaq	4(%rax), %r9
	mulsd	%xmm5, %xmm1
	cmpq	%r9, %rcx
	jl	.L4
	movsd	32(%rdx,%rsi), %xmm0
	movq	%r8, %rdi
	andl	$3, %edi
	mulsd	%xmm1, %xmm0
	cmpq	$2, %rdi
	je	.L23
	cmpq	$3, %rdi
	je	.L24
	cmpq	$1, %rdi
	je	.L54
	addsd	%xmm0, %xmm6
.L27:
	leaq	5(%rax), %r8
	mulsd	%xmm5, %xmm1
	cmpq	%r8, %rcx
	jl	.L4
	movsd	40(%rdx,%rsi), %xmm0
	movq	%r9, %rdi
	andl	$3, %edi
	mulsd	%xmm1, %xmm0
	cmpq	$2, %rdi
	je	.L28
	cmpq	$3, %rdi
	je	.L29
	cmpq	$1, %rdi
	je	.L55
	addsd	%xmm0, %xmm6
.L32:
	leaq	6(%rax), %r9
	mulsd	%xmm5, %xmm1
	cmpq	%rcx, %r9
	jg	.L4
	movsd	48(%rdx,%rsi), %xmm0
	movq	%r8, %rdi
	andl	$3, %edi
	mulsd	%xmm1, %xmm0
	cmpq	$2, %rdi
	je	.L33
	cmpq	$3, %rdi
	je	.L34
	cmpq	$1, %rdi
	je	.L56
	addsd	%xmm0, %xmm6
.L37:
	mulsd	%xmm5, %xmm1
	addq	$7, %rax
	cmpq	%rcx, %rax
	jg	.L4
	mulsd	56(%rdx,%rsi), %xmm1
	movq	%r9, %rax
	andl	$3, %eax
	cmpq	$2, %rax
	je	.L38
	cmpq	$3, %rax
	je	.L39
	cmpq	$1, %rax
	je	.L40
	addsd	%xmm1, %xmm6
.L4:
	addsd	%xmm6, %xmm3
	addsd	%xmm7, %xmm3
	addsd	%xmm4, %xmm3
	movapd	%xmm3, %xmm0
	ret
	.p2align 4,,10
	.p2align 3
.L51:
	addsd	%xmm0, %xmm3
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L52:
	addsd	%xmm0, %xmm3
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L14:
	addsd	%xmm0, %xmm4
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L13:
	addsd	%xmm0, %xmm7
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L18:
	addsd	%xmm0, %xmm7
	jmp	.L22
	.p2align 4,,10
	.p2align 3
.L53:
	addsd	%xmm0, %xmm3
	jmp	.L22
	.p2align 4,,10
	.p2align 3
.L19:
	addsd	%xmm0, %xmm4
	jmp	.L22
	.p2align 4,,10
	.p2align 3
.L2:
	testq	%rsi, %rsi
	jle	.L57
	movsd	8(%rdx), %xmm0
	pxor	%xmm4, %xmm4
	movapd	%xmm5, %xmm1
	movl	$8, %esi
	movapd	%xmm4, %xmm7
	movapd	%xmm4, %xmm3
	movl	$1, %eax
	mulsd	%xmm5, %xmm0
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L24:
	addsd	%xmm0, %xmm4
	jmp	.L27
	.p2align 4,,10
	.p2align 3
.L23:
	addsd	%xmm0, %xmm7
	jmp	.L27
	.p2align 4,,10
	.p2align 3
.L54:
	addsd	%xmm0, %xmm3
	jmp	.L27
	.p2align 4,,10
	.p2align 3
.L28:
	addsd	%xmm0, %xmm7
	jmp	.L32
	.p2align 4,,10
	.p2align 3
.L55:
	addsd	%xmm0, %xmm3
	jmp	.L32
	.p2align 4,,10
	.p2align 3
.L29:
	addsd	%xmm0, %xmm4
	jmp	.L32
	.p2align 4,,10
	.p2align 3
.L56:
	addsd	%xmm0, %xmm3
	jmp	.L37
	.p2align 4,,10
	.p2align 3
.L34:
	addsd	%xmm0, %xmm4
	jmp	.L37
	.p2align 4,,10
	.p2align 3
.L33:
	addsd	%xmm0, %xmm7
	jmp	.L37
.L38:
	addsd	%xmm1, %xmm7
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L40:
	addsd	%xmm1, %xmm3
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L39:
	addsd	%xmm1, %xmm4
	jmp	.L4
.L57:
	pxor	%xmm4, %xmm4
	movapd	%xmm4, %xmm7
	movapd	%xmm4, %xmm3
	jmp	.L4
	.cfi_endproc
.LFE0:
	.size	poly_opt, .-poly_opt
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
