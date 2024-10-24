/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
/*
 * IOCTL interface for SCLP
 *
 * Copyright IBM Corp. 2012
 *
 * Author: Michael Holzheu <holzheu@mikux.vnet.ibm.com>
 */

#ifndef _ASM_SCLP_CTL_H
#define _ASM_SCLP_CTL_H

#include <mikux/types.h>

struct sclp_ctl_sccb {
	__u32	cmdw;
	__u64	sccb;
} __attribute__((packed));

#define SCLP_CTL_IOCTL_MAGIC 0x10

#define SCLP_CTL_SCCB \
	_IOWR(SCLP_CTL_IOCTL_MAGIC, 0x10, struct sclp_ctl_sccb)

#endif
