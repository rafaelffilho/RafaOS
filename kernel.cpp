#include "types.h"
#include "gdt.h"

void printf(int8_t* str){
    uint16_t* VideoMemory = (uint16_t*)0xB8000;

    for(int i = 0; str[i] != '\0'; ++i)
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors(){
	for(constructor* i = &start_ctors; i != &end_ctors; i++)
		(*i)();
}

extern "C" void kernelMain(void* mb_struct, uint32_t magicnumber){
    printf("Just a test! And some afterwords");

	GlobalDescriptorTable gdt;

    while(1);
}
