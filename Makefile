#tools
ASM = nasm
CC = gcc 
LD = ld
QEMU = qemu-system-i386


#flags
ASMFLAGS = -f elf32
CFLAGS = -m32 -ffreestanding -fno-pie -c 
LDFlAGS = -m elf_i386 -T linker.ld


OUT = build
BIN = bin
#files
BOOT_ASM = src/bootloader/boot.asm
KERNEL_ASM = src/kernel/kernel_entry.asm
KERNEL_C   = src/kernel/kernel.c
SCREEN_C = src/kernel/screen/screen.c
#outputs and binaries
BOOT_BIN = bin/boot.bin

KERNEL_ENTRY_O = build/kernel_entry.o
KERNEL_C_O = build/kernel.o
KERNEL_ELF = build/kernel.elf
KERNEL_BIN = bin/kernel.bin

SCREEN_O = build/screen/screen.o
SCREEN = build/screen

Image = bin/os-image.bin



all: $(Image)

$(OUT):
	mkdir -p $(OUT)

$(BIN):
	mkdir -p $(BIN) 

$(SCREEN):
	mkdir -p $(SCREEN)

#bootloader
$(BOOT_BIN): $(BOOT_ASM) | $(BIN)
	$(ASM) -f bin  $< -o $@
#kernel
$(KERNEL_ENTRY_O): $(KERNEL_ASM) | $(BIN)
	$(ASM) $(ASMFLAGS) $< -o $@

$(SCREEN_O):$(SCREEN_C) | $(SCREEN)
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL_C_O): $(KERNEL_C) | $(OUT)
	$(CC) $(CFLAGS) -nostdlib $< -o $@

$(KERNEL_ELF): $(KERNEL_ENTRY_O) $(KERNEL_C_O) $(SCREEN_O)
	$(LD) $(LDFlAGS) -o $@ $^


$(KERNEL_BIN): $(KERNEL_ELF)
	objcopy -O binary $< $@
#Image
$(Image): $(BOOT_BIN) $(KERNEL_BIN)
	cat $^ > $@

run: $(Image)
	$(QEMU) -fda $(Image) 

#cLean
cLean: $(BIN) $(OUT)
	rm -rf $^




