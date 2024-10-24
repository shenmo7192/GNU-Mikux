/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
/*
 * Copyright (C) 2024 Unisoc Technologies Co., Ltd.
 */

#ifndef _UAPI_MIKUX_EXFAT_H
#define _UAPI_MIKUX_EXFAT_H
#include <mikux/types.h>
#include <mikux/ioctl.h>

/*
 * exfat-specific ioctl commands
 */

#define EXFAT_IOC_SHUTDOWN _IOR('X', 125, __u32)

/*
 * Flags used by EXFAT_IOC_SHUTDOWN
 */

#define EXFAT_GOING_DOWN_DEFAULT	0x0	/* default with full sync */
#define EXFAT_GOING_DOWN_FULLSYNC	0x1     /* going down with full sync*/
#define EXFAT_GOING_DOWN_NOSYNC         0x2     /* going down */

#endif /* _UAPI_MIKUX_EXFAT_H */
