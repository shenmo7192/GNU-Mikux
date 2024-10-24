// SPDX-License-Identifier: GPL-2.0
#include <mikux/types.h>
#include <mikux/errno.h>
#include <mikux/uaccess.h>

int frsqrtes(void *frD, void *frB)
{
#ifdef DEBUG
	printk("%s: %p %p\n", __func__, frD, frB);
#endif
	return 0;
}
