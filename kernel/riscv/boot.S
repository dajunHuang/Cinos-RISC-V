#include <asm/encoding.h>
#include <config.h>

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

	/*
	 * Set the trap handler. This must happen after initializing gp because
	 * the handler may use it.
	 */
	la	t0, trap_entry
	csrw	stvec, t0

	/*
	 * Mask all interrupts. Interrupts are disabled globally (in m/sstatus)
	 * for U-Boot, but we will need to read m/sip to determine if we get an
	 * IPI
	 */
	csrw	sie, zero

	/* check if hart is within range */
	/* tp: hart id */
	li	t0, CONFIG_NR_CPUS
	bge	tp, t0, hart_out_of_bounds_loop
	/* set xSIE bit to receive IPIs */
	li	t0, SIE_SSIE
	csrs	sie, t0

/*
 * Set stackpointer in internal/ex RAM to call board_init_f
 */
call_board_init_f:
	la	t0, stacks_end
	and	t0, t0, -16
	slli	t1, tp, CONFIG_STACK_SIZE_SHIFT
	sub	sp, t0, t1

/* clear stack */
clear_stack:
	li	t1, 1
	slli	t1, t1, CONFIG_STACK_SIZE_SHIFT
	sub	t1, sp, t1
clear_stack_loop:
	sd	zero, 0(t1)		/* t1 is always 16 byte aligned */
	addi	t1, t1, 8
	blt	t1, sp, clear_stack_loop

	/* goto C */
	tail start

hart_out_of_bounds_loop:
	/* Harts in this loop are out of bounds, increase CONFIG_NR_CPUS. */
	wfi
	j	hart_out_of_bounds_loop

.section .data
.align  12
.global stacks_start, stacks_end
stacks_start:
	.skip CONFIG_STACK_SIZE
stacks_end:
