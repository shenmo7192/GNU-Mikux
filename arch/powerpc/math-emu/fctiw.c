// SPDX-License-Identifier: GPL-2.0
#include <mikux/types.h>
#include <mikux/errno.h>
#include <mikux/uaccess.h>

#include <asm/sfp-machine.h>
#include <math-emu/soft-fp.h>
#include <math-emu/double.h>

int
fctiw(u32 *frD, void *frB)
{
	FP_DECL_D(B);
	FP_DECL_EX;
	unsigned int r;

	FP_UNPACK_DP(B, frB);
	FP_TO_INT_D(r, B, 32, 1);
	frD[1] = r;

#ifdef DEBUG
	printk("%s: D %p, B %p: ", __func__, frD, frB);
	dump_double(frD);
	printk("\n");
#endif

	return 0;
}
