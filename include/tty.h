#ifndef TTY_H
#define TTY_H

#include "types.h"

void init_tty(void);
void printf(char *);
void printc(char);
void print_dec(uint32_t);

#endif