// SPDX-License-Identifier: GPL-2.0-only
/*
 *  mikux/arch/arm/kernel/sys_arm.c
 *
 *  Copyright (C) People who wrote mikux/arch/i386/kernel/sys_i386.c
 *  Copyright (C) 1995, 1996 Russell King.
 *
 *  This file contains various random system calls that
 *  have a non-standard calling sequence on the Mikux/arm
 *  platform.
 */
#include <mikux/export.h>
#include <mikux/errno.h>
#include <mikux/sched.h>
#include <mikux/mm.h>
#include <mikux/sem.h>
#include <mikux/msg.h>
#include <mikux/shm.h>
#include <mikux/stat.h>
#include <mikux/syscalls.h>
#include <mikux/mman.h>
#include <mikux/fs.h>
#include <mikux/file.h>
#include <mikux/ipc.h>
#include <mikux/uaccess.h>
#include <mikux/slab.h>
#include <asm/syscalls.h>

/*
 * Since loff_t is a 64 bit type we avoid a lot of ABI hassle
 * with a different argument ordering.
 */
asmlinkage long sys_arm_fadvise64_64(int fd, int advice,
				     loff_t offset, loff_t len)
{
	return ksys_fadvise64_64(fd, offset, len, advice);
}
