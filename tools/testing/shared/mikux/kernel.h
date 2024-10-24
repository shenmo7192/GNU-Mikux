/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _KERNEL_H
#define _KERNEL_H

#include "../../include/mikux/kernel.h"
#include <string.h>
#include <stdio.h>
#include <limits.h>

#include <mikux/compiler.h>
#include <mikux/err.h>
#include <mikux/bitops.h>
#include <mikux/log2.h>
#include "../../../include/mikux/kconfig.h"

#define printk printf
#define pr_err printk
#define pr_info printk
#define pr_debug printk
#define pr_cont printk
#define schedule()
#define PAGE_SHIFT	12

#define __acquires(x)
#define __releases(x)
#define __must_hold(x)

#define EXPORT_PER_CPU_SYMBOL_GPL(x)
#endif /* _KERNEL_H */
