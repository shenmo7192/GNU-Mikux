/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef _MIKUX_UTIME_H
#define _MIKUX_UTIME_H

#include <mikux/types.h>

struct utimbuf {
	__kernel_old_time_t actime;
	__kernel_old_time_t modtime;
};

#endif
