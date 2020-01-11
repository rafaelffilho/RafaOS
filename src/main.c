#include <descriptor_tables.h>
#include <kheap.h>
#include <paging.h>
#include <timer.h>
#include <tty.h>
#include <types.h>

void kmain(void *mb_struct, uint32_t magicnumber) {
	init_tty();
	printf("Hello World!\n");
	init_descriptor_tables();

	uint32_t a = kmalloc(8);
	uint32_t b = kmalloc(8);

	kfree(a);
	kfree(b);

	__asm__ volatile("sti");
	init_timer(50);

	initialize_paging();
	printf("Initialized paging!\n");

	uint32_t *ptr           = (uint32_t *) 0xA0000000;
	uint32_t  do_page_fault = *ptr;
	(void) do_page_fault;

	for (;;) {}
}
