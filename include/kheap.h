#ifndef HEAP_H
#define HEAP_H

#include "types.h"

uint32_t kmalloc_a(uint32_t);
uint32_t kmalloc_p(uint32_t, uint32_t *);
uint32_t kmalloc_ap(uint32_t, uint32_t *);
uint32_t kmalloc(uint32_t);

#endif    // !HEAP_H