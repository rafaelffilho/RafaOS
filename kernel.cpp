void printf(char* str){
    unsigned short* VideoMemory = (unsigned short*)0xb8000;

    for(int i = 0; str[i] != '\0'; ++i)
        VideoMemory[i] = (VideoMemory[i] & 0xff00) | str[i];
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors(){
	for(constructor* i = &start_ctors; i != end_ctors; i++)
		(*i)();
}

extern "C" void kernelMain(void* mb_struct, unsigned int magicnumber){
    printf("Just a test!");

    while(1);
}
