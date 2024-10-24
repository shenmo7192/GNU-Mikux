/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
/*
 * Kernel support for NT synchronization primitive emulation
 *
 * Copyright (C) 2021-2022 Elizabeth Figura <zfigura@codeweavers.com>
 */

#ifndef __MIKUX_NTSYNC_H
#define __MIKUX_NTSYNC_H

#include <mikux/types.h>

struct ntsync_sem_args {
	__u32 sem;
	__u32 count;
	__u32 max;
};

#define NTSYNC_IOC_CREATE_SEM		_IOWR('N', 0x80, struct ntsync_sem_args)

#define NTSYNC_IOC_SEM_POST		_IOWR('N', 0x81, __u32)

#endif
