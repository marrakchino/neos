/* Multiboot specific values, see 
https://www.gnu.org/software/grub/manual/multiboot/multiboot.html 
for details */
#define MULTIBOOT_HEADER_FLAGS      0x10002 
#define MULTIBOOT_HEADER_MAGIC      0x1BADB002
#define MULTIBOOT_HEADER_CHKSUM     -(MULTIBOOT_HEADER_FLAGS + MULTIBOOT_HEADER_MAGIC)
#define KERNEL_STACK_SIZE           0x4000 /* 16 KB */

    .text
    .comm stack,KERNEL_STACK_SIZE,32
    .comm multiboot_info,4,4
    .comm multiboot_magic,4,4

.global entry
entry:
	movl	%eax,multiboot_magic
	movl	%ebx,multiboot_info	

    /* set up a stack for kernel code */
    leal stack,%esp
    addl KERNEL_STACK_SIZE,%esp
    xorl %ebp,%ebp

	movl	$_edata,%edi
zeroize:	
    movl	%eax,(%edi) 
	xorl	%eax,%eax
	addl	$4,%edi 
	cmpl	$mem_heap_end,%edi 
	jb	zeroize 

    .p2align 2
0:  .long MULTIBOOT_HEADER_MAGIC, MULTIBOOT_HEADER_FLAGS, MULTIBOOT_HEADER_CHKSUM, 0b
	.long _start, _edata, __bss_end, entry

    /* kernel entry point */
    call start_kernel

/* this label should never be reached */
infinite_loop:
    hlt
    jmp infinite_loop
