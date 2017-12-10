PXE = boot.pxe

KERNEL = kernel.bin

SRCS = $(wildcard *.S *.c)

OBJS = $(strip crt0.o $(filter-out crt0.o,$(notdir $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRCS))))))

CC = gcc -std=c99
AS = gcc -std=c99
LD = ld
QEMU = /usr/bin/qemu-system-i386

# CFLAGS = -m32 -g -gstabs -std=c99 -nostdinc -fno-stack-protector -I.
CFLAGS = -m32 -Wall -Werror -g -gstabs -std=c99 -nostdinc -fno-stack-protector -I.
ASFLAGS = -m32 -DASSEMBLER -g -gstabs -I.
LDFLAGS = -melf_i386

# -S option is to pause the system 
# QEMUOPTS = -no-kvm -net nic -net user,tftp="`pwd`",bootfile="$(PXE)" -boot n -cpu pentium -rtc base=localtime -m 64M -gdb tcp::1234 -S
QEMUOPTS = -cpu pentium -rtc base=localtime -m 64M -gdb tcp::1234 -kernel kernel.bin

.PHONY: all
all: kernel.bin

kernel.bin: kernel.lds $(OBJS) 
	$(LD) $(LDFLAGS) -e entry -Tkernel.lds $(OBJS) -o $@

clean:
	$(RM) $(OBJS) $(KERNEL) 

run:
	$(QEMU) $(QEMUOPTS)

