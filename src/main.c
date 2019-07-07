#include "../include/tty.h"
#include "../include/types.h"

void kmain(void *mb_struct, uint32_t magicnumber) {
	init_tty();
	printf("Hello World!");
	for (;;) {}
}
