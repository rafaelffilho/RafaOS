#ifndef COMMON_H
#define COMMON_H

#include "tty.h"
#include "types.h"

#define PANIC(a) panic(a, __FILE__, __LINE__)

int      memset(void *, uint32_t, uint32_t);
void     outb(uint16_t, uint8_t);
uint8_t  inb(uint16_t);
uint16_t inw(uint16_t);

void panic(char *, char *, int);

#endif    // !COMMON_H