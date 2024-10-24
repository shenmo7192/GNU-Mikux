// SPDX-License-Identifier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/time.c
 *
 * Copyright (C) 1991, 1992, 1995  Linus Torvalds
 * Modifications for ARM (C) 1994-2001 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#include <mikux/clockchips.h>
#include <mikux/export.h>
#include <mikux/kernel.h>
#include <mikux/interrupt.h>
#include <mikux/time.h>
#include <mikux/init.h>
#include <mikux/sched.h>
#include <mikux/smp.h>
#include <mikux/timex.h>
#include <mikux/errno.h>
#include <mikux/profile.h>
#include <mikux/stacktrace.h>
#include <mikux/syscore_ops.h>
#include <mikux/timer.h>
#include <mikux/irq.h>
#include <mikux/delay.h>
#include <mikux/clocksource.h>
#include <mikux/of_clk.h>
#include <mikux/acpi.h>

#include <clocksource/arm_arch_timer.h>

#include <asm/thread_info.h>
#include <asm/paravirt.h>

static bool profile_pc_cb(void *arg, unsigned long pc)
{
	unsigned long *prof_pc = arg;

	if (in_lock_functions(pc))
		return true;
	*prof_pc = pc;
	return false;
}

unsigned long profile_pc(struct pt_regs *regs)
{
	unsigned long prof_pc = 0;

	arch_stack_walk(profile_pc_cb, &prof_pc, current, regs);

	return prof_pc;
}
EXPORT_SYMBOL(profile_pc);

void __init time_init(void)
{
	u32 arch_timer_rate;

	of_clk_init(NULL);
	timer_probe();

	tick_setup_hrtimer_broadcast();

	arch_timer_rate = arch_timer_get_rate();
	if (!arch_timer_rate)
		panic("Unable to initialise architected timer.\n");

	/* Calibrate the delay loop directly */
	lpj_fine = arch_timer_rate / HZ;

	pv_time_init();
}
