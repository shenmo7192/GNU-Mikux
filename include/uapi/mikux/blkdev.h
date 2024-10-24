/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef _UAPI_MIKUX_BLKDEV_H
#define _UAPI_MIKUX_BLKDEV_H

#include <mikux/ioctl.h>
#include <mikux/types.h>

/*
 * io_uring block file commands, see IORING_OP_URING_CMD.
 * It's a different number space from ioctl(), reuse the block's code 0x12.
 */
#define BLOCK_URING_CMD_DISCARD			_IO(0x12, 0)

#endif
