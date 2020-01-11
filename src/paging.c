#include <common.h>
#include <kheap.h>
#include <paging.h>

page_directory_t *kernel_directory  = 0;
page_directory_t *current_directory = 0;

uint32_t *frames;
uint32_t  nframes;

extern uint32_t placement_address;
extern heap_t * kheap;

#define INDEX_FROM_BIT(a) (a / 32)
#define OFFSET_FROM_BIT(a) (a % 32)

static void set_frame(uint32_t frame_addr) {
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx   = INDEX_FROM_BIT(frame);
	uint32_t off   = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32_t frame_addr) {
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx   = INDEX_FROM_BIT(frame);
	uint32_t off   = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << off);
}

static uint32_t test_frame(uint32_t frame_addr) {
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx   = INDEX_FROM_BIT(frame);
	uint32_t off   = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1 << off));
}

static uint32_t first_frame() {
	for (uint32_t i = 0; i < INDEX_FROM_BIT(nframes); ++i) {
		if (frames[i] != 0xFFFFFFFF) {
			for (uint32_t j = 0; j < 32; ++j) {
				uint32_t to_test = 0x1 << j;
				if (!(frames[i] & to_test)) return i * 32 + j;
			}
		}
	}
}

void alloc_frame(page_t *page, int is_kernel, int is_writable) {
	if (page->frame != 0) return;

	uint32_t idx = first_frame();
	if (idx == (uint32_t) -1) panic("No free fames", __FILE__, __LINE__);

	set_frame(idx * 0x1000);
	page->present = 1;
	page->rw      = is_writable ? 1 : 0;
	page->user    = is_kernel ? 0 : 1;
	page->frame   = idx;
}

void free_frame(page_t *page) {
	uint32_t frame = page->frame;
	if (!frame) return;

	clear_frame(frame);
	page->frame = 0x0;
}

void initialize_paging() {
	uint32_t mem_end_page = 0x1000000;

	nframes = mem_end_page / 0x1000;
	frames  = (uint32_t *) kmalloc(INDEX_FROM_BIT(nframes));
	memset(frames, 0, INDEX_FROM_BIT(nframes));

	kernel_directory = (page_directory_t *) kmalloc_a(sizeof(page_directory_t));
	memset(kernel_directory, 0, sizeof(page_directory_t));
	current_directory = kernel_directory;

	for (int i = 0; i < placement_address; i += 0x1000)
		alloc_frame(get_page(i, 1, kernel_directory), 0, 0);

	for (int i = KHEAP_START; i < KHEAP_INITIAL_SIZE; i += 0x1000)
		get_page(i, 1, kernel_directory);

	for (int i = KHEAP_START; i < KHEAP_INITIAL_SIZE; i += 0x1000)
		alloc_frame(get_page(i, 1, kernel_directory), 0, 0);

	register_interrupt_handler(14, page_fault);

	switch_page_directory(kernel_directory);

	kheap = create_heap(KHEAP_START, KHEAP_START + KHEAP_INITIAL_SIZE, 0xCFFFF000,
	                    0, 0);
}

void switch_page_directory(page_directory_t *dir) {
	current_directory = dir;
	uint32_t cr0;
	__asm__ volatile("mov %0, %%cr3" ::"r"(&dir->tables_physical));
	__asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
	cr0 |= 0x80000000;
	__asm__ volatile("mov %0, %%cr0" ::"r"(cr0));
}

page_t *get_page(uint32_t address, int make, page_directory_t *dir) {
	address /= 0x1000;
	uint32_t table_idx = address / 1024;
	if (dir->tables[table_idx]) {
		return &dir->tables[table_idx]->pages[address % 1024];
	} else if (make) {
		uint32_t tmp;
		dir->tables[table_idx] =
		  (page_table_t *) kmalloc_ap(sizeof(page_table_t), &tmp);
		memset(dir->tables[table_idx], 0, 0x1000);
		dir->tables_physical[table_idx] = tmp | 0x7;

		return &dir->tables[table_idx]->pages[address % 1024];
	} else {
		return 0;
	}
}

void page_fault(registers_t regs) {
	uint32_t faulting_address;
	__asm__ volatile("mov %%cr2, %0" : "=r"(faulting_address));

	int present  = !(regs.err_code & 0x1);
	int rw       = regs.err_code & 0x2;
	int us       = regs.err_code & 0x4;
	int reserved = regs.err_code & 0x8;
	int id       = regs.err_code & 0x10;

	printf("Page fault! (");
	if (present) printf("present ");
	if (rw) printf("read-only ");
	if (us) printf("user-mode ");
	if (reserved) printf("reserved ");
	printf(") at ");
	print_dec(faulting_address);
	printc('\n');

	panic("Page fault", __FILE__, __LINE__);
}