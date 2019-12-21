#include "../include/isr.h"

#include "../include/common.h"
#include "../include/tty.h"

void isr_handler(registers_t regs) {
	char a[256];

	// TODO: for some reason this shit does not print the interrupt number
	printf("received interrupt: ");
	printf(itoa(regs.int_no, a, 10));
	printf("\n");
}