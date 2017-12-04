#ifndef __ASM_WRAPPER_H__
#define __ASM_WRAPPER_H__

static void __inline__ sti(void){
	__asm__ volatile("sti:::memory");
}

static void __inline__ hlt(void){
	__asm__ volatile("hlt:::memory");
}

static void __inline__ cli(void){
	__asm__ volatile("cli:::memory");
}

static void __inline__ outb(unsigned short port, unsigned char data){
	__asm__ volatile("outb %0, %1" : : "a" (data) : "Nd" (port));
}

static unsigned char __inline__ inb(unsigned short port){
	unsigned char data;
	__asm__ volatile("inb %1, %0" : "=a" (data) : "d" (port));
	return data;
}

#endif
