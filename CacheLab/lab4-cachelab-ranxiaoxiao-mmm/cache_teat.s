	.file	"cache_teat.cpp"
	.text
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.globl	main
	.type	main, @function
main:
.LFB1731:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	-16384(%rsp), %r11
.LPSRL0:
	subq	$4096, %rsp
	orq	$0, (%rsp)
	cmpq	%r11, %rsp
	jne	.LPSRL0
	subq	$2128, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$0, -18496(%rbp)
	movq	$0, -18488(%rbp)
	movq	$0, -18480(%rbp)
	movq	$0, -18472(%rbp)
	movq	$0, -18464(%rbp)
	movq	$0, -18456(%rbp)
	movl	$1, -18496(%rbp)
	leaq	-18448(%rbp), %rax
	movl	$9216, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movl	$1, -18448(%rbp)
	leaq	-9232(%rbp), %rax
	movl	$9216, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movl	$2, -9232(%rbp)
	movl	$0, -18508(%rbp)
	jmp	.L2
.L7:
	movl	$0, -18504(%rbp)
	jmp	.L3
.L6:
	movl	-18508(%rbp), %eax
	movl	%eax, -18500(%rbp)
	jmp	.L4
.L5:
	movl	-18504(%rbp), %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18496(%rbp)
	movl	-18504(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18492(%rbp)
	movl	-18504(%rbp), %eax
	addl	$2, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18488(%rbp)
	movl	-18504(%rbp), %eax
	addl	$3, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18484(%rbp)
	movl	-18504(%rbp), %eax
	addl	$4, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18480(%rbp)
	movl	-18504(%rbp), %eax
	addl	$5, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18476(%rbp)
	movl	-18504(%rbp), %eax
	addl	$6, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18472(%rbp)
	movl	-18504(%rbp), %eax
	addl	$7, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18468(%rbp)
	movl	-18504(%rbp), %eax
	addl	$8, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18464(%rbp)
	movl	-18504(%rbp), %eax
	addl	$9, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18460(%rbp)
	movl	-18504(%rbp), %eax
	addl	$10, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18456(%rbp)
	movl	-18504(%rbp), %eax
	addl	$11, %eax
	movslq	%eax, %rcx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	-18448(%rbp,%rax,4), %eax
	movl	%eax, -18452(%rbp)
	movl	-18496(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movl	-18504(%rbp), %eax
	movslq	%eax, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	1(%rax), %ecx
	movl	-18492(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	2(%rax), %ecx
	movl	-18488(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	3(%rax), %ecx
	movl	-18484(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	4(%rax), %ecx
	movl	-18480(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	5(%rax), %ecx
	movl	-18476(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	6(%rax), %ecx
	movl	-18472(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	7(%rax), %ecx
	movl	-18468(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	8(%rax), %ecx
	movl	-18464(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	9(%rax), %ecx
	movl	-18460(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	10(%rax), %ecx
	movl	-18456(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	movl	-18504(%rbp), %eax
	leal	11(%rax), %ecx
	movl	-18452(%rbp), %edx
	movl	-18500(%rbp), %eax
	movslq	%eax, %rsi
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	movl	%edx, -9232(%rbp,%rax,4)
	addl	$1, -18500(%rbp)
.L4:
	movl	-18508(%rbp), %eax
	addl	$11, %eax
	cmpl	%eax, -18500(%rbp)
	jle	.L5
	addl	$12, -18504(%rbp)
.L3:
	cmpl	$47, -18504(%rbp)
	jle	.L6
	addl	$12, -18508(%rbp)
.L2:
	cmpl	$47, -18508(%rbp)
	jle	.L7
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1731:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2226:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L12
	cmpl	$65535, -8(%rbp)
	jne	.L12
	leaq	_ZStL8__ioinit(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	leaq	__dso_handle(%rip), %rax
	movq	%rax, %rdx
	leaq	_ZStL8__ioinit(%rip), %rax
	movq	%rax, %rsi
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
.L12:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2226:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2227:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2227:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.hidden	__dso_handle
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
