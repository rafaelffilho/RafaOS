# RafaOS

A basic kernel written in C to learn more about OS Dev

Dependecies:
* clang 8
* ld.lld
* nasm
* make
* grub
* xorriso (maybe the package name will be libisoburn)

Steps to compile and execute:
```bash
$ mkdir build
$ make kernel.iso
$ qemu-system-x86_64 -monitor stdio kernel.iso
```