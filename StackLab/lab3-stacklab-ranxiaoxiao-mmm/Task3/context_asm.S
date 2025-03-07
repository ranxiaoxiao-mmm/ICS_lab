.text

.globl __ctx_save
__ctx_save:
    mov %rbx, 0x18(%rdi)
    mov (%rsp), %rbx
    mov %rbx, 0x0(%rdi)
    mov %rbp, 0x8(%rdi)
    mov %rsp, 0x10(%rdi)
    mov %r12, 0x20(%rdi)
    mov %r13, 0x28(%rdi)
    mov %r14, 0x30(%rdi)
    mov %r15, 0x38(%rdi)
    mov %rcx, 0x40(%rdi)
    mov %rdx, 0x48(%rdi)
    mov %rdi, 0x50(%rdi)
    xor %rax,%rax
    ret

// TODO

.globl __ctx_restore
__ctx_restore:
    mov %rsi,%rax
    mov 0x8(%rdi),%rbp
    mov 0x10(%rdi),%rsp
    mov 0x20(%rdi), %r12
    mov 0x28(%rdi), %r13
    mov 0x30(%rdi), %r14
    mov 0x38(%rdi), %r15
    mov 0x40(%rdi), %rcx
    mov 0x48(%rdi), %rdx
    mov 0x0(%rdi), %rbx
    mov %rbx, (%rsp)
    mov 0x18(%rdi), %rbx
    mov 0x50(%rdi), %rdi
    ret
    

// TODO