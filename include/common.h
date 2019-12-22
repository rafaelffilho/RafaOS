#ifndef COMMON_H
#define COMMON_H

#include "types.h"

int      memset(void *, uint32_t, uint32_t);
void     outb(uint16_t, uint8_t);
uint8_t  inb(uint16_t);
uint16_t inw(uint16_t);

#endif    // !COMMON_H