SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRCS = $(wildcard $(SRCDIR)/*.S $(SRCDIR)/*.c)
OBJS = $(strip $(patsubst $(SRCDIR)/%.S,$(OBJDIR)/%.o,$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))))

KERNEL = $(BINDIR)/kernel.bin
LINKER_SCRIPT = scripts/kernel.ld

CC = gcc 
AS = gcc 
LD = ld
OBJCOPY = objcopy
OBJDUMP = objdump
QEMU = /usr/bin/qemu-system-i386
CFLAGS = -std=c99 -m32 -Wall -Werror -Wformat -Wunused -g -gstabs -nostdinc -fno-stack-protector -fno-builtin -Iinclude
ASFLAGS = -std=c99 -m32 -DASSEMBLER -g -gstabs -Iinclude
LDFLAGS = -melf_i386

.PHONY: all gdb
all: $(KERNEL)

GDBPORT = $(shell expr `id -u` % 5000 + 25000)
QEMUOPTS = -cpu pentium -rtc base=localtime -m 64M -gdb tcp::$(GDBPORT) -kernel $(KERNEL)

.gdbinit:
	touch .gdbinit 

.PHONY: gdb
gdb: .gdbinit
	echo "target remote :$(GDBPORT)" >> .gdbinit

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	$(AS) $(ASFLAGS) -c -o $@ $<

$(KERNEL): $(LINKER_SCRIPT) $(OBJS) 
	$(LD) $(LDFLAGS) -T$(LINKER_SCRIPT) $(OBJS) -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS) $(KERNEL) .gdbinit

run: $(KERNEL)
	$(QEMU) $(QEMUOPTS)

.PHONY: tags
tags:
	ctags $(SRCS)

.PHONY: license
license:
	bash scripts/copy_license_header.sh
