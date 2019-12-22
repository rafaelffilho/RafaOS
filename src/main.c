#include <descriptor_tables.h>
#include <timer.h>
#include <tty.h>
#include <types.h>

void kmain(void *mb_struct, uint32_t magicnumber) {
	init_tty();
	printf("Hello World!\n");
	init_descriptor_tables();

	__asm__ volatile ("sti");
	init_timer(50);

	for (;;) {}
}
