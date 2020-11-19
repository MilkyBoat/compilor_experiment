# 函数 mult
    .text
    .globl mult
    .type mult, @function
mult:
    movl 4(%esp), %eax
    imull 8(%esp), %eax
    ret

# 全局变量
	.globl	x
	.data
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	1
	.globl	n
	.bss
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.zero	4

# 常量
    .section .rodata
STR0:
    .string "%d"
STR1:
    .string "%d\n"

# 主函数
    .text
    .globl main
    .type main, @function
main:
# scanf("%d", &n);
    pushl $n
    pushl $STR0
    call scanf
    addl $8, %esp
L1:
# end if n<=0
    movl n, %eax
    cmpl $0, %eax
    jle L2
# calculate x * n
    pushl x
    pushl n
    call mult
    addl $8, %esp
# x = x * n;
    movl %eax, x
# n--;
    subl $1, n
    jmp L1
L2:
# printf("%d\n", x);
    pushl x
    pushl $STR1
    call printf
    addl $8, %esp
# return 0;
    xorl %eax, %eax
    ret
# 可执行堆栈段
    .section .note.GNU-stack,"",@progbits
