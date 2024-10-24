// SPDX-License-Identifier: GPL-2.0-only
/*
 *  mikux/arch/arm/kernel/time.c
 *
 *  Copyright (C) 1991, 1992, 1995  Linus Torvalds
 *  Modifications for ARM (C) 1994-2001 Russell King
 *
 *  This file contains the ARM-specific time handling details:
 *  reading the RTC at bootup, etc...
 */
#include <mikux/clockchips.h>
#include <mikux/clocksource.h>
#include <mikux/errno.h>
#include <mikux/export.h>
#include <mikux/init.h>
#include <mikux/interrupt.h>
#include <mikux/irq.h>
#include <mikux/kernel.h>
#include <mikux/of_clk.h>
#include <mikux/profile.h>
#include <mikux/sched.h>
#include <mikux/sched_clock.h>
#include <mikux/smp.h>
#include <mikux/time.h>
#include <mikux/timex.h>
#include <mikux/timer.h>

#include <asm/mach/arch.h>
#include <asm/mach/time.h>
#include <asm/stacktrace.h>
#include <asm/thread_info.h>

#if defined(CONFIG_RTC_DRV_CMOS) || defined(CONFIG_RTC_DRV_CMOS_MODULE) || \
    defined(CONFIG_NVRAM) || defined(CONFIG_NVRAM_MODULE)
/* this needs a better home */
DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL(rtc_lock);
#endif	/* pc-style 'CMOS' RTC support */

/* change this if you have some constant time drift */
#define USECS_PER_JIFFY	(1000000/HZ)

#ifdef CONFIG_SMP
unsigned long profile_pc(struct pt_regs *regs)
{
	struct stackframe frame;

	if (!in_lock_functions(regs->ARM_pc))
		return regs->ARM_pc;

	arm_get_current_stackframe(regs, &frame);
	do {
		int ret = unwind_frame(&frame);
		if (ret < 0)
			return 0;
	} while (in_lock_functions(frame.pc));

	return frame.pc;
}
EXPORT_SYMBOL(profile_pc);
#endif

static void dummy_clock_access(struct timespec64 *ts)
{
	ts->tv_sec = 0;
	ts->tv_nsec = 0;
}

static clock_access_fn __read_persistent_clock = dummy_clock_access;

void read_persistent_clock64(struct timespec64 *ts)
{
	__read_persistent_clock(ts);
}

int __init register_persistent_clock(clock_access_fn read_persistent)
{
	/* Only allow the clockaccess functions to be registered once */
	if (__read_persistent_clock == dummy_clock_access) {
		if (read_persistent)
			__read_persistent_clock = read_persistent;
		return 0;
	}

	return -EINVAL;
}

void __init time_init(void)
{
	if (machine_desc->init_time) {
		machine_desc->init_time();
	} else {
#ifdef CONFIG_COMMON_CLK
		of_clk_init(NULL);
#endif
		timer_probe();
		tick_setup_hrtimer_broadcast();
	}
}
