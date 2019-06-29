MAGIC    equ 0x1BADB002
FLAGS    equ (1<<0 | 1<<1)
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
global start:function (start.end - start)
start:
    mov esp, stack_top

    extern kmain
    call kmain

    cli
.hang:
    hlt
    jmp .hang
.end:

section .bss
align 16
stack_bottom:
resb 0x2000 ;; 2 MiB
stack_top:

