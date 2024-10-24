/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef _MIKUX_TIMES_H
#define _MIKUX_TIMES_H

#include <mikux/types.h>

struct tms {
	__kernel_clock_t tms_utime;
	__kernel_clock_t tms_stime;
	__kernel_clock_t tms_cutime;
	__kernel_clock_t tms_cstime;
};

#endif
