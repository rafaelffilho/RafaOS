#include <kheap.h>
#include <types.h>

extern uint32_t end;
uint32_t        placement_address = (uint32_t) &end;

uint32_t kmalloc_a(uint32_t sz) {
	if (placement_address & 0xFFFFF000) {
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}

	uint32_t tmp = placement_address;
	placement_address += sz;
	return tmp;
}

uint32_t kmalloc_p(uint32_t sz, uint32_t *phys) {
	*phys = placement_address;

	uint32_t tmp = placement_address;
	placement_address += sz;
	return tmp;
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys) {
	if (placement_address & 0xFFFFF000) {
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}

	*phys = placement_address;

	uint32_t tmp = placement_address;
	placement_address += sz;
	return tmp;
}

uint32_t kmalloc(uint32_t sz) {
	uint32_t tmp = placement_address;
	placement_address += sz;
	return tmp;
}
