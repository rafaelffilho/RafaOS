#include "types.h"
#include "gdt.h"
#include "interrupts.h"

void printf(int8_t* str){
  static uint16_t* VideoMemory = (uint16_t*)0xB8000;

	static uint8_t x = 0;
	static uint8_t y = 0;

    for(int i = 0; str[i] != '\0'; ++i){ 
		switch(str[i]){
		case '\n':
			y++;
			x = 0;
			break;
		default:
			VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
			x++;
			break;
		}
		if(x >= 80){
			y++;
			x = 0;
		}
		if(y >= 25){
			for(y = 0; y < 25; y++)
				for(x = 0; x < 80; x++)
        			VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
			y = 0;
			x = 0;
		}
	}
}

extern "C" void kmain(void* mb_struct, uint32_t magicnumber){
  printf((char*)"\nJust a test!\n");
	printf((char*)"And some afterwords");	

  while(1);
}
