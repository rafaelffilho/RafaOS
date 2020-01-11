#ifndef HEAP_H
#define HEAP_H

#include "ordered_array.h"
#include "types.h"

#define KHEAP_START 0xC0000000
#define KHEAP_INITIAL_SIZE 0x100000
#define HEAP_INDEX_SIZE 0x20000
#define HEAP_MAGIC 0x123890AB
#define HEAP_MIN_SIZE 0x70000

struct header_struct {
	uint32_t magic;
	uint8_t  is_hole;
	uint32_t size;
};
typedef struct header_struct header_t;

struct footer_struct {
	uint32_t  magic;
	header_t *header;
};
typedef struct footer_struct footer_t;

struct heap_struct {
	ordered_array_t index;
	uint32_t        start_address;
	uint32_t        end_address;
	uint32_t        max_address;
	uint8_t         supervisor;
	uint8_t         read_only;
};
typedef struct heap_struct heap_t;

uint32_t kmalloc_a(uint32_t);
uint32_t kmalloc_p(uint32_t, uint32_t *);
uint32_t kmalloc_ap(uint32_t, uint32_t *);
uint32_t kmalloc(uint32_t);
void     kfree(void *);

heap_t *create_heap(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);
void *  alloc(uint32_t, uint8_t, heap_t *);
void    free(void *, heap_t *);

#endif    // !HEAP_H