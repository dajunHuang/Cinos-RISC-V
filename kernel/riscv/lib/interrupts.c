// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2016-17 Microsemi Corporation.
 * Padmarao Begari, Microsemi Corporation <padmarao.begari@microsemi.com>
 *
 * Copyright (C) 2017 Andes Technology Corporation
 * Rick Chen, Andes Technology Corporation <rick@andestech.com>
 *
 * Copyright (C) 2019 Sean Anderson <seanga2@gmail.com>
 */


#include <asm/encoding.h>
#include <types.h>
#include <ptrace.h>

int interrupt_init(void)
{
	return 0;
}

/*
 * enable interrupts
 */
void enable_interrupts(void)
{
}

/*
 * disable interrupts
 */
int disable_interrupts(void)
{
	return 0;
}

ulong handle_trap(ulong cause, ulong epc, ulong tval, struct pt_regs *regs)
{
	ulong is_irq, irq;

	is_irq = (cause & MCAUSE_INT);
	irq = (cause & ~MCAUSE_INT);

	if (is_irq) {
		switch (irq) {
		case IRQ_M_EXT:
		case IRQ_S_EXT:
			// external_interrupt(0);	/* handle external interrupt */
			break;
		case IRQ_M_TIMER:
		case IRQ_S_TIMER:
			// timer_interrupt(0);	/* handle timer interrupt */
			break;
		default:
			// _exit_trap(cause, epc, tval, regs);
			break;
		};
	} else {
		// _exit_trap(cause, epc, tval, regs);
	}

	return epc;
}

