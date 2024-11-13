#include <asm/encoding.h>

.section ".text.boot"

.globl _start
_start:
	/*
	 * Save hart id and dtb pointer. The thread pointer register is not
	 * modified by C code. It is used by secondary_hart_loop.
	 */
	mv	tp, a0
	mv	s1, a1

	/*
	 * Set the global data pointer to a known value in case we get a very
	 * early trap. The global data pointer will be set its actual value only
	 * after it has been initialized.
	 */
	mv	gp, zero

	# /* Mask all interrupts */
	# csrw sie, zero

	# /* set the stack of SP, size 4KB */
	# la sp, stacks_start
	# li t0, 4096
	# add sp, sp, t0

	/* goto C */
	tail start

.section .data
.align  12
.global stacks_start
stacks_start:
	.skip 4096
