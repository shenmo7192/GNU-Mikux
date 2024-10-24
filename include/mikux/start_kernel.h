/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_START_KERNEL_H
#define _MIKUX_START_KERNEL_H

#include <mikux/linkage.h>
#include <mikux/init.h>

/* Define the prototype for start_kernel here, rather than cluttering
   up something else. */

extern asmlinkage void __init __noreturn start_kernel(void);

#endif /* _MIKUX_START_KERNEL_H */
