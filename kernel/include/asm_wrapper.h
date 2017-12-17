#ifndef __ASM_WRAPPER_H__
#define __ASM_WRAPPER_H__


static void __inline__ sti(void){
	__asm__ __volatile__("sti:::memory");
}

static void __inline__ hlt(void){
	__asm__ __volatile__("hlt:::memory");
}

static void __inline__ cli(void){
	__asm__ __volatile__("cli:::memory");
}

static void __inline__ outb(unsigned short port, unsigned char data){
	__asm__ __volatile__("outb %0, %1" : : "a" (data) , "Nd" (port));
}

static unsigned char __inline__ inb(unsigned short port){
	unsigned char data;
	__asm__ __volatile__("inb %1, %0" : "=a" (data) : "d" (port));
	return data;
}

static inline void stosl(void* addr, int data, int count){
    __asm__ __volatile__("cld; rep stosl" : "=D" (addr), "=c" (count) :
                      "0" (addr), "1" (count), "a" (data) :
                      "memory", "cc");
}

#endif
