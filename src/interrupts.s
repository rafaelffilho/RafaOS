section .text
global isr0:function (isr0.end - isr0)
isr0:
  cli
  push byte 0
  push byte 0

  jmp isr_common_stub
.end:

global isr_common_stub:function (isr_common_stub.end - isr_common_stub)
isr_common_stub:
  pusha

  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  extern isr_handler
  call isr_handler

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  popa

  add esp, 8
  sti
  iret
.end:

global irq_common_stub:function (irq_common_stub.end - irq_common_stub)
irq_common_stub:
  pusha

  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  extern irq_handler
  call irq_handler

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  popa

  add esp, 8
  sti
  iret
.end:

%macro ISR_NOERRCODE 1
global isr%1:function (isr%1.end - isr%1)
isr%1:
  cli
  push byte 0
  push byte %1

  jmp isr_common_stub
.end:
%endmacro

%macro ISR_ERRCODE 1
global isr%1:function (isr%1.end - isr%1)
isr%1:
  cli
  push byte %1

  jmp isr_common_stub
.end:
%endmacro

%macro IRQ 2
global irq%1:function (irq%1.end - irq%1)
irq%1:
    cli
    push byte 0
    push byte %2

    jmp irq_common_stub
.end:
%endmacro

ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_NOERRCODE 11
ISR_NOERRCODE 12
ISR_NOERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

IRQ   0,  32
IRQ   1,  33
IRQ   2,  34
IRQ   3,  35
IRQ   4,  36
IRQ   5,  37
IRQ   6,  38
IRQ   7,  39
IRQ   8,  40
IRQ   9,  41
IRQ  10,  42
IRQ  11,  43
IRQ  12,  44
IRQ  13,  45
IRQ  14,  46
IRQ  15,  47