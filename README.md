# LagroOS

A simple x86 operating system written from scratch in Assembly and C.

This project is being developed step by step to understand low-level system programming, bootloaders, protected mode, memory layout, VGA text mode, and eventually interrupts, drivers, and multitasking.

## Features

### Bootloader
- Custom bootloader written in NASM
- Loads the kernel from disk
- Sets up a stack
- Switches from Real Mode to Protected Mode
- Loads a Global Descriptor Table (GDT)

### Protected Mode
- Enters 32-bit Protected Mode
- Initializes segment registers
- Jumps to the kernel entry point

### Kernel
- Written in C with a small Assembly entry stub
- Freestanding environment (`-ffreestanding`)
- Direct VGA text mode output

### VGA Text Driver
- Character output
- String output
- Output at specific coordinates
- Screen clearing
- Basic cursor management
- Control character handling:
  - `\n` (newline)
  - `\t` (tab)
  - `\r` (carriage return)
  - `\b` (backspace)

## Project Structure

```text
.
├── bin
│   ├── boot.bin
│   ├── kernel.bin
│   └── os-image.bin
│
├── build
│   ├── kernel.elf
│   ├── kernel.o
│   ├── kernel_entry.o
│   └── screen
│       └── screen.o
│
├── src
│   ├── bootloader
│   │   └── boot.asm
│   │
│   └── kernel
│       ├── kernel.c
│       ├── kernel_entry.asm
│       └── screen
│           ├── screen.c
│           └── screen.h
│
├── linker.ld
├── Makefile
└── README.md
```

## Build Requirements

### Linux

Required tools:

- NASM
- GCC (with 32-bit support)
- Binutils
- QEMU

Arch Linux:

```bash
sudo pacman -S nasm gcc binutils qemu
```

If compiling 32-bit code:

```bash
sudo pacman -S lib32-gcc-libs
```

## Building

```bash
make
```

Generated files:

```text
bin/boot.bin
bin/kernel.bin
bin/os-image.bin
```

## Running

```bash
make run
```

QEMU will boot the generated image:

```text
os-image.bin
```

## Current Learning Goals

- [x] Custom bootloader
- [x] Disk loading
- [x] Global Descriptor Table (GDT)
- [x] Protected Mode
- [x] C kernel
- [x] VGA text output
- [x] Basic terminal functions
- [ ] Screen scrolling
- [ ] Interrupt Descriptor Table (IDT)
- [ ] Exception handlers
- [ ] Keyboard driver
- [ ] Shell
- [ ] Memory management
- [ ] Paging
- [ ] User mode
- [ ] Filesystem

## Notes

This project is educational and focuses on understanding how operating systems work internally rather than creating a production-ready OS.

## Author

Oualid Benkhaira (LAGRO)
