CROSS_COMPILE=riscv64-unknown-linux-gnu-

all: u-boot opensbi kernel

UBOOT_DIR=u-boot
UBOOT_BIN=$(UBOOT_DIR)/u-boot.bin
$(UBOOT_BIN):
	make -C $(UBOOT_DIR) CROSS_COMPILE=$(CROSS_COMPILE) qemu-riscv64_smode_defconfig
	make -C $(UBOOT_DIR) CROSS_COMPILE=$(CROSS_COMPILE) -j8
u-boot: $(UBOOT_BIN)

OPENSBI_DIR=opensbi
OPENSBI_BIN=$(OPENSBI_DIR)/build/platform/generic/firmware/fw_jump.bin
$(OPENSBI_BIN):
	make -C $(OPENSBI_DIR) CROSS_COMPILE=$(CROSS_COMPILE) PLATFORM=generic PLATFORM_RISCV_XLEN=64 FW_JUMP=y FW_JUMP_ADDR=0x80200000
opensbi: $(OPENSBI_BIN)

KERNEL_DIR=kernel
KERNEL_BIN=$(KERNEL_DIR)/kernel.bin
$(KERNEL_BIN):
	make -C $(KERNEL_DIR) CROSS_COMPILE=$(CROSS_COMPILE)
kernel: $(KERNEL_BIN)

QEMU=qemu-system-riscv64

qemu: 
	$(QEMU) -nographic -M virt -cpu rv64 -m 4G -smp 4 -bios $(OPENSBI_BIN) -kernel $(KERNEL_BIN) # device loader,file="$(KERNEL_BIN)",addr=0x80200000

qemu-gdb: 
	$(QEMU) -s -S -nographic -M virt -cpu rv64 -m 4G -smp 4 -bios $(OPENSBI_BIN) -kernel $(KERNEL_BIN)

clean:
	make -C kernel clean
