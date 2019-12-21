#include "../include/descriptor_tables.h"
#include "../include/tty.h"
#include "../include/types.h"

void kmain(void *mb_struct, uint32_t magicnumber) {
	init_tty();
	printf("Hello World!");
	init_descriptor_tables();
	__asm__ volatile("int $0x3");
	__asm__ volatile("int $0x4");
	for (;;) {}
}
