/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * M-mode Trap Handler Code for RISC-V Core
 *
 * Copyright (c) 2017 Microsemi Corporation.
 * Copyright (c) 2017 Padmarao Begari <Padmarao.Begari@microsemi.com>
 *
 * Copyright (C) 2017 Andes Technology Corporation
 * Rick Chen, Andes Technology Corporation <rick@andestech.com>
 *
 * Copyright (C) 2018, Bin Meng <bmeng.cn@gmail.com>
 */

#include <asm/encoding.h>

#define ld		ld
#define sd		sd
#define 8	8

	.text

	/* trap entry */
	.align 6
	.global trap_entry
trap_entry:
	addi sp, sp, -32 * 8
	sd x1,   1 * 8(sp)
	sd x2,   2 * 8(sp)
	sd x3,   3 * 8(sp)
	sd x4,   4 * 8(sp)
	sd x5,   5 * 8(sp)
	sd x6,   6 * 8(sp)
	sd x7,   7 * 8(sp)
	sd x8,   8 * 8(sp)
	sd x9,   9 * 8(sp)
	sd x10, 10 * 8(sp)
	sd x11, 11 * 8(sp)
	sd x12, 12 * 8(sp)
	sd x13, 13 * 8(sp)
	sd x14, 14 * 8(sp)
	sd x15, 15 * 8(sp)
	sd x16, 16 * 8(sp)
	sd x17, 17 * 8(sp)
	sd x18, 18 * 8(sp)
	sd x19, 19 * 8(sp)
	sd x20, 20 * 8(sp)
	sd x21, 21 * 8(sp)
	sd x22, 22 * 8(sp)
	sd x23, 23 * 8(sp)
	sd x24, 24 * 8(sp)
	sd x25, 25 * 8(sp)
	sd x26, 26 * 8(sp)
	sd x27, 27 * 8(sp)
	sd x28, 28 * 8(sp)
	sd x29, 29 * 8(sp)
	sd x30, 30 * 8(sp)
	sd x31, 31 * 8(sp)
	csrr a0, scause
	csrr a1, sepc
	csrr a2, stval
	mv a3, sp
	jal handle_trap
	csrw sepc, a0

	ld x1,   1 * 8(sp)
	ld x3,   3 * 8(sp)
	ld x4,   4 * 8(sp)
	ld x5,   5 * 8(sp)
	ld x6,   6 * 8(sp)
	ld x7,   7 * 8(sp)
	ld x8,   8 * 8(sp)
	ld x9,   9 * 8(sp)
	ld x10, 10 * 8(sp)
	ld x11, 11 * 8(sp)
	ld x12, 12 * 8(sp)
	ld x13, 13 * 8(sp)
	ld x14, 14 * 8(sp)
	ld x15, 15 * 8(sp)
	ld x16, 16 * 8(sp)
	ld x17, 17 * 8(sp)
	ld x18, 18 * 8(sp)
	ld x19, 19 * 8(sp)
	ld x20, 20 * 8(sp)
	ld x21, 21 * 8(sp)
	ld x22, 22 * 8(sp)
	ld x23, 23 * 8(sp)
	ld x24, 24 * 8(sp)
	ld x25, 25 * 8(sp)
	ld x26, 26 * 8(sp)
	ld x27, 27 * 8(sp)
	ld x28, 28 * 8(sp)
	ld x29, 29 * 8(sp)
	ld x30, 30 * 8(sp)
	ld x31, 31 * 8(sp)
	ld x2,   2 * 8(sp)
	addi sp, sp, 32 * 8
	sret
