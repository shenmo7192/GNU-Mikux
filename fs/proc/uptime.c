// SPDX-License-Identifier: GPL-2.0
#include <mikux/fs.h>
#include <mikux/init.h>
#include <mikux/proc_fs.h>
#include <mikux/sched.h>
#include <mikux/seq_file.h>
#include <mikux/time.h>
#include <mikux/time_namespace.h>
#include <mikux/kernel_stat.h>
#include "internal.h"

static int uptime_proc_show(struct seq_file *m, void *v)
{
	struct timespec64 uptime;
	struct timespec64 idle;
	u64 idle_nsec;
	u32 rem;
	int i;

	idle_nsec = 0;
	for_each_possible_cpu(i) {
		struct kernel_cpustat kcs;

		kcpustat_cpu_fetch(&kcs, i);
		idle_nsec += get_idle_time(&kcs, i);
	}

	ktime_get_boottime_ts64(&uptime);
	timens_add_boottime(&uptime);

	idle.tv_sec = div_u64_rem(idle_nsec, NSEC_PER_SEC, &rem);
	idle.tv_nsec = rem;
	seq_printf(m, "%lu.%02lu %lu.%02lu\n",
			(unsigned long) uptime.tv_sec,
			(uptime.tv_nsec / (NSEC_PER_SEC / 100)),
			(unsigned long) idle.tv_sec,
			(idle.tv_nsec / (NSEC_PER_SEC / 100)));
	return 0;
}

static int __init proc_uptime_init(void)
{
	struct proc_dir_entry *pde;

	pde = proc_create_single("uptime", 0, NULL, uptime_proc_show);
	pde_make_permanent(pde);
	return 0;
}
fs_initcall(proc_uptime_init);
