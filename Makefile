ASM = nasm
ASMFlAGS = -f bin

SRC = src
OUT = build

Boot_Src = $(SRC)/bootloader/boot.asm
Kernel_Src = $(SRC)/kernel/kernel.asm

Boot_Bin = $(OUT)/boot.bin
Kernel_Bin = $(OUT)/kernel.bin
Image = $(OUT)/os-image.bin

QEMU = qemu-system-i386

all: $(Image)

$(Out):
	mkdir -p $(OUT)

#bootloader
$(Boot_Bin): $(Boot_Src) | $(OUT)
	$(ASM) $(ASMFLAGS) $< -o $@
#kernel
$(Kernel_Bin): $(Kernel_Src) | $(OUT)
	$(ASM) $(ASMFLAGS) $< -o $@
#Image
$(Image): $(Boot_Bin) $(Kernel_Bin)
	cat $^ > $@

run: $(Image)
	$(QEMU) -drive format=raw,file=$(Image)

cLean:
	rm -rf $(Out)




