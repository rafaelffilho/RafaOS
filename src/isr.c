#include <common.h>
#include <isr.h>
#include <tty.h>

isr_t interrupt_handlers[256];

void isr_handler(registers_t regs) {
	// TODO: for some reason this shit does not print the interrupt number
	printf("received interrupt (isr): ");
	print_dec(regs.int_no);
	printc('\n');
}

void irq_handler(registers_t regs) {
	if (regs.int_no >= 40) outb(0xA0, 0x20);

	outb(0x20, 0x20);

	printf("received interrupt (irq): ");
	print_dec(regs.int_no);
	printc('\n');

	if (interrupt_handlers[regs.int_no] != 0) {
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
	interrupt_handlers[n] = handler;
}