/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of California
 */

#ifndef _ASM_RISCV_ASM_H
#define _ASM_RISCV_ASM_H

#ifdef __ASSEMBLY__
#define __ASM_STR(x)	x
#else
#define __ASM_STR(x)	#x
#endif

#define __REG_SEL(a, b)	__ASM_STR(a)

#define REG_L		__REG_SEL(ld, lw)
#define REG_S		__REG_SEL(sd, sw)
#define SZREG		__REG_SEL(8, 4)
#define LGREG		__REG_SEL(3, 2)

#ifdef __ASSEMBLY__
#define RISCV_PTR		.dword
#define RISCV_SZPTR		8
#define RISCV_LGPTR		3
#else
#define RISCV_PTR		".dword"
#define RISCV_SZPTR		"8"
#define RISCV_LGPTR		"3"
#endif

#define RISCV_INT		__ASM_STR(.word)
#define RISCV_SZINT		__ASM_STR(4)
#define RISCV_LGINT		__ASM_STR(2)

#define RISCV_SHORT		__ASM_STR(.half)
#define RISCV_SZSHORT		__ASM_STR(2)
#define RISCV_LGSHORT		__ASM_STR(1)

#endif /* _ASM_RISCV_ASM_H */
