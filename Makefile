GCC:=i686-elf-gcc
LD:=i686-elf-ld
AS:=i686-elf-as
QEMU:=qemu-system-i386

KERNEL_OUTFILE:= kernel.bin
ISO_OUTFILE:= AngelOS_0.0.0-alpha.iso

KERNEL_SOURCES_ASM:= kernel/boot/main.asm
KERNEL_SOURCES_NTV:= kernel/core/*.c kernel/support/*.c

CFLAGS:= -Wall -Wextra -Werror=write-strings -Werror=uninitialized -O2 -Winline -Iinclude/
DEBUG:= -D__ANGOS_DEBUG=1 -g3 -O0 -Werror

default: $(KERNEL_SOURCES_NTV) $(KERNEL_SOURCES_ASM)
	@echo "build: Preparing..."
	@[ -d build ] || mkdir -p build
	@cd build
	@echo "build: Compiling boot assembly..."
	@$(AS) $(KERNEL_SOURCES_ASM) -o boot.o
	@echo "build: Compiling native kernel..."
	@$(GCC) -c $(KERNEL_SOURCES_NTV) $(CFLAGS)
	@echo "build: Packaging final kernel binary..."
	@$(LD) -T linker.ld *.o -o $(KERNEL_OUTFILE)
	@echo "Done, removing build files..."
	@rm -rfv *.o

qemu: $(KERNEL_OUTFILE)
	$(QEMU) -kernel $(KERNEL_OUTFILE)

clean:
	rm -rfv *.o *.bin
