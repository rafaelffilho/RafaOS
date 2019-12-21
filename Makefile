CFLAGS = -std=c99 -Wall -Werror -m32 -nostdlib -fno-builtin -fno-stack-protector -ffreestanding

objects  = build/loader.o build/main.o build/tty.o build/gdt.o
objects += build/descriptor_table.o build/common.o
objects += build/isr.o build/interrupts.o

build/%.o: src/%.c
	clang $(CFLAGS) -o $@ -c $<

build/%.o: src/%.s
	nasm -o $@ $< -f elf32

build/kernel.bin: src/linker.ld $(objects)
	ld.lld -error-limit=0 -T $< -o $@ $(objects)

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
	qemu-system-x86_64 $< &

all: kernel.iso
	echo "done"
