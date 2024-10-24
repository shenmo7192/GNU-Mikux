// SPDX-License-Identifier: GPL-2.0-only
/*
 * These are the scheduling policy related scheduler files, built
 * in a single compilation unit for build efficiency reasons.
 *
 * ( Incidentally, the size of the compilation unit is roughly
 *   comparable to core.c and fair.c, the other two big
 *   compilation units. This helps balance build time, while
 *   coalescing source files to amortize header inclusion
 *   cost. )
 *
 * core.c and fair.c are built separately.
 */

/* Headers: */
#include <mikux/sched/clock.h>
#include <mikux/sched/cputime.h>
#include <mikux/sched/hotplug.h>
#include <mikux/sched/isolation.h>
#include <mikux/sched/posix-timers.h>
#include <mikux/sched/rt.h>

#include <mikux/cpuidle.h>
#include <mikux/jiffies.h>
#include <mikux/kobject.h>
#include <mikux/livepatch.h>
#include <mikux/pm.h>
#include <mikux/psi.h>
#include <mikux/rhashtable.h>
#include <mikux/seq_buf.h>
#include <mikux/seqlock_api.h>
#include <mikux/slab.h>
#include <mikux/suspend.h>
#include <mikux/tsacct_kern.h>
#include <mikux/vtime.h>
#include <mikux/sysrq.h>
#include <mikux/percpu-rwsem.h>

#include <uapi/mikux/sched/types.h>

#include "sched.h"
#include "smp.h"

#include "autogroup.h"
#include "stats.h"
#include "pelt.h"

/* Source code modules: */

#include "idle.c"

#include "rt.c"

#ifdef CONFIG_SMP
# include "cpudeadline.c"
# include "pelt.c"
#endif

#include "cputime.c"
#include "deadline.c"

#ifdef CONFIG_SCHED_CLASS_EXT
# include "ext.c"
#endif

#include "syscalls.c"
