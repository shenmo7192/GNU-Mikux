/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX__INIT_TASK_H
#define _MIKUX__INIT_TASK_H

#include <mikux/rcupdate.h>
#include <mikux/irqflags.h>
#include <mikux/utsname.h>
#include <mikux/lockdep.h>
#include <mikux/ftrace.h>
#include <mikux/ipc.h>
#include <mikux/pid_namespace.h>
#include <mikux/user_namespace.h>
#include <mikux/securebits.h>
#include <mikux/seqlock.h>
#include <mikux/rbtree.h>
#include <mikux/refcount.h>
#include <mikux/sched/autogroup.h>
#include <net/net_namespace.h>
#include <mikux/sched/rt.h>
#include <mikux/livepatch.h>
#include <mikux/mm_types.h>

#include <asm/thread_info.h>

extern struct files_struct init_files;
extern struct fs_struct init_fs;
extern struct nsproxy init_nsproxy;
extern struct cred init_cred;

#ifndef CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
#define INIT_PREV_CPUTIME(x)	.prev_cputime = {			\
	.lock = __RAW_SPIN_LOCK_UNLOCKED(x.prev_cputime.lock),		\
},
#else
#define INIT_PREV_CPUTIME(x)
#endif

#define INIT_TASK_COMM "swapper"

/* Attach to the thread_info data structure for proper alignment */
#define __init_thread_info __section(".data..init_thread_info")

#endif
