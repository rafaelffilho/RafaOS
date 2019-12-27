CFLAGS  = -Iinclude -I. -std=c99 -Wall -m32
CFLAGS += -fno-stack-protector -ffreestanding -nostdlib -fno-builtin

SOURCES =                \
	src/common.c           \
	src/descriptor_table.c \
	src/gdt.s              \
	src/interrupts.s       \
	src/isr.c              \
	src/kheap.c            \
	src/loader.s           \
	src/main.c             \
	src/paging.c           \
	src/timer.c            \
	src/tty.c

OBJECTS = $(patsubst src/%.s,build/%.o,$(patsubst src/%.c,build/%.o,$(SOURCES)))

build/%.o: src/%.c
	gcc $(CFLAGS) -o $@ -c $<

build/%.o: src/%.s
	nasm -o $@ $< -f elf32

build/kernel.bin: src/linker.ld $(OBJECTS)
	ld.lld -T $< -o $@ $(OBJECTS)

clean:
	rm build/* &
	rm kernel.iso &

kernel.iso: build/kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: kernel.iso
	qemu-system-i386 $< &

all: kernel.iso
	echo "done"
