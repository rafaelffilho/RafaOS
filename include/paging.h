#ifndef PAGING_H
#define PAGING_H

#include "common.h"
#include "isr.h"
#include "types.h"

struct page {
	uint32_t present : 1;
	uint32_t rw : 1;
	uint32_t user : 1;
	uint32_t accessed : 1;
	uint32_t dirty : 1;
	uint32_t unused : 7;
	uint32_t frame : 20;
};
typedef struct page page_t;

struct page_table {
	page_t pages[1024];
};
typedef struct page_table page_table_t;

struct page_directory {
	page_table_t *tables[1024];
	uint32_t      tables_physical[1024];
	uint32_t      physical_address;
};
typedef struct page_directory page_directory_t;

void    initialize_paging();
void    switch_page_directory(page_directory_t *);
page_t *get_page(uint32_t, int, page_directory_t *);
void    page_fault(registers_t);

#endif    // !PAGING_H