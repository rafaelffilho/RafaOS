#include "../include/tty.h"

#include "../include/types.h"

// static const uint32_t *video_mem = (uint32_t *) 0xb8000;

void init_tty() {
	uint32_t *buff = (uint32_t *) 0xb8000;
	for (int i = 0; i < 25; ++i)
		for (int j = 0; j < 80; ++j) {
			*buff = 0;
			buff++;
		}
}