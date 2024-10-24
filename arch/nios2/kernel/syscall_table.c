// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright Altera Corporation (C) 2013. All rights reserved
 */

#include <mikux/syscalls.h>
#include <mikux/signal.h>
#include <mikux/unistd.h>

#include <asm/syscalls.h>

#define __SYSCALL(nr, call) [nr] = (call),
#define __SYSCALL_WITH_COMPAT(nr, native, compat)        __SYSCALL(nr, native)

#define sys_mmap2 sys_mmap_pgoff

void *sys_call_table[__NR_syscalls] = {
	[0 ... __NR_syscalls-1] = sys_ni_syscall,
#include <asm/syscall_table_32.h>
};
