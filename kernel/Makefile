CROSS_COMPILE?=riscv64-unknown-elf-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy

COPS += -g -O0 -Wall -mcmodel=medany -mabi=lp64 -march=rv64imafd -fno-PIE -fno-omit-frame-pointer -fno-builtin
AOPS += -D__ASSEMBLY__
LOPS += -nostdlib -nostartfiles

C_FILES = $(wildcard *.c) $(wildcard **/*.c)
ASM_FILES = $(wildcard *.S) $(wildcard **/*.S)

OBJ_FILES = $(C_FILES:%.c=%_c.o)
OBJ_FILES += $(ASM_FILES:%.S=%_s.o)

INCLUDES := -I.
INCLUDES += -I../include
INCLUDES += -I../include/asm
INCLUDES += -I../include/qemu_virt
INCLUDES += -Iinclude
INCLUDES += -Iinclude/libc
INCLUDES += -Idriver/hal/include
INCLUDES += -Idriver/qemu_virt

all: kernel

%_c.o: %.c
	$(CC) $(COPS) $(INCLUDES) -c $< -o $@

%_s.o: %.S
	$(CC) $(COPS) $(AOPS) $(INCLUDES) -c $< -o $@

kernel: kernel.bin

kernel.bin:	$(OBJ_FILES) kernel.ld
	$(LD) -T kernel.ld -o kernel.elf $(OBJ_FILES)
	$(OBJCOPY) -O binary $(LOPS) kernel.elf kernel.bin

clean:
	-rm $(OBJ_FILES) kernel.elf kernel.bin
