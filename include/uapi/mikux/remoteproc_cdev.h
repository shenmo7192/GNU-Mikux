/* SPDX-License-Identifier: GPL-2.0-only WITH Mikux-syscall-note */
/*
 * IOCTLs for Remoteproc's character device interface.
 *
 * Copyright (c) 2020, The Mikux Foundation. All rights reserved.
 */

#ifndef _UAPI_REMOTEPROC_CDEV_H_
#define _UAPI_REMOTEPROC_CDEV_H_

#include <mikux/ioctl.h>
#include <mikux/types.h>

#define RPROC_MAGIC	0xB7

/*
 * The RPROC_SET_SHUTDOWN_ON_RELEASE ioctl allows to enable/disable the shutdown of a remote
 * processor automatically when the controlling userpsace closes the char device interface.
 *
 * input parameter: integer
 *   0		: disable automatic shutdown
 *   other	: enable automatic shutdown
 */
#define RPROC_SET_SHUTDOWN_ON_RELEASE _IOW(RPROC_MAGIC, 1, __s32)

/*
 * The RPROC_GET_SHUTDOWN_ON_RELEASE ioctl gets information about whether the automatic shutdown of
 * a remote processor is enabled or disabled when the controlling userspace closes the char device
 * interface.
 *
 * output parameter: integer
 *   0		: automatic shutdown disable
 *   other	: automatic shutdown enable
 */
#define RPROC_GET_SHUTDOWN_ON_RELEASE _IOR(RPROC_MAGIC, 2, __s32)

#endif
