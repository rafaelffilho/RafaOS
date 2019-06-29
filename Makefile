CFLAGS = -std=c99 -Wall -Werror -m32 -nostdlib -fno-builtin -fno-stack-protector -ffreestanding

objects = loader.o kernel.o

%.o: %.cpp
	clang $(CFLAGS) -o $@ -c $<

%.o: %.s
	nasm -o $@ $< -f elf32

kernel.bin: linker.ld $(objects)
	ld.lld -T $< -o $@ $(objects)

install: kernel.bin
	sudo cp $< /boot/kernel.bin

clean: 
	rm *.o
	rm *.bin
	rm *.iso

kernel.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: kernel.iso
	qemu-system-x86_64 $< &
