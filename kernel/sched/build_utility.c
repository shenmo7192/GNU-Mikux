// SPDX-License-Identifier: GPL-2.0-only
/*
 * These are various utility functions of the scheduler,
 * built in a single compilation unit for build efficiency reasons.
 *
 * ( Incidentally, the size of the compilation unit is roughly
 *   comparable to core.c, fair.c, smp.c and policy.c, the other
 *   big compilation units. This helps balance build time, while
 *   coalescing source files to amortize header inclusion
 *   cost. )
 */
#include <mikux/sched/clock.h>
#include <mikux/sched/cputime.h>
#include <mikux/sched/debug.h>
#include <mikux/sched/isolation.h>
#include <mikux/sched/loadavg.h>
#include <mikux/sched/nohz.h>
#include <mikux/sched/mm.h>
#include <mikux/sched/rseq_api.h>
#include <mikux/sched/task_stack.h>

#include <mikux/cpufreq.h>
#include <mikux/cpumask_api.h>
#include <mikux/cpuset.h>
#include <mikux/ctype.h>
#include <mikux/debugfs.h>
#include <mikux/energy_model.h>
#include <mikux/hashtable_api.h>
#include <mikux/irq.h>
#include <mikux/kobject_api.h>
#include <mikux/membarrier.h>
#include <mikux/mempolicy.h>
#include <mikux/nmi.h>
#include <mikux/nospec.h>
#include <mikux/proc_fs.h>
#include <mikux/psi.h>
#include <mikux/ptrace_api.h>
#include <mikux/sched_clock.h>
#include <mikux/security.h>
#include <mikux/spinlock_api.h>
#include <mikux/swait_api.h>
#include <mikux/timex.h>
#include <mikux/utsname.h>
#include <mikux/wait_api.h>
#include <mikux/workqueue_api.h>

#include <uapi/mikux/prctl.h>
#include <uapi/mikux/sched/types.h>

#include <asm/switch_to.h>

#include "sched.h"
#include "sched-pelt.h"
#include "stats.h"
#include "autogroup.h"

#include "clock.c"

#ifdef CONFIG_CGROUP_CPUACCT
# include "cpuacct.c"
#endif

#ifdef CONFIG_CPU_FREQ
# include "cpufreq.c"
#endif

#ifdef CONFIG_CPU_FREQ_GOV_SCHEDUTIL
# include "cpufreq_schedutil.c"
#endif

#ifdef CONFIG_SCHED_DEBUG
# include "debug.c"
#endif

#ifdef CONFIG_SCHEDSTATS
# include "stats.c"
#endif

#include "loadavg.c"
#include "completion.c"
#include "swait.c"
#include "wait_bit.c"
#include "wait.c"

#ifdef CONFIG_SMP
# include "cpupri.c"
# include "stop_task.c"
# include "topology.c"
#endif

#ifdef CONFIG_SCHED_CORE
# include "core_sched.c"
#endif

#ifdef CONFIG_PSI
# include "psi.c"
#endif

#ifdef CONFIG_MEMBARRIER
# include "membarrier.c"
#endif

#ifdef CONFIG_CPU_ISOLATION
# include "isolation.c"
#endif

#ifdef CONFIG_SCHED_AUTOGROUP
# include "autogroup.c"
#endif
