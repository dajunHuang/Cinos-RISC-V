CROSS_COMPILE?=riscv64-unknown-linux-gnu-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

COPS += -g -O0 -Wall -mcmodel=medany -mabi=lp64 -march=rv64imafd -fno-PIE -fno-omit-frame-pointer -fno-builtin -nostdlib -nostartfiles
AOPS += -D__ASSEMBLY__
LOPS += 

C_FILES = $(shell find ./ -name '*.c')
ASM_FILES = $(shell find ./ -name '*.S')

OBJ_FILES = $(C_FILES:%.c=%_c.o)
OBJ_FILES += $(ASM_FILES:%.S=%_s.o)

INCLUDES := $(addprefix -I, $(shell find ./ -type d)) $(addprefix -I, $(shell find ../include -type d))

all: kernel

%_c.o: %.c
	$(CC) $(COPS) $(INCLUDES) -c $< -o $@

%_s.o: %.S
	$(CC) $(COPS) $(AOPS) $(INCLUDES) -c $< -o $@

kernel:	$(OBJ_FILES) kernel.ld
	$(LD) -T kernel.ld -o kernel.elf $(OBJ_FILES)
	$(OBJDUMP) -D kernel.elf > kernel.asm
	$(OBJCOPY) -O binary kernel.elf kernel.bin

clean:
	-rm $(OBJ_FILES) kernel.elf kernel.bin kernel.asm
