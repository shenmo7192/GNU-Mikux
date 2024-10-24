// SPDX-License-Identifier: GPL-2.0-only
/*
 *
 * Copyright (C) 2014 ARM Limited
 */

#include <mikux/clocksource.h>
#include <mikux/io.h>
#include <mikux/of.h>
#include <mikux/of_address.h>
#include <mikux/sched_clock.h>

#define SYS_24MHZ 0x05c

static void __iomem *versatile_sys_24mhz;

static u64 notrace versatile_sys_24mhz_read(void)
{
	return readl(versatile_sys_24mhz);
}

static int __init versatile_sched_clock_init(struct device_node *node)
{
	void __iomem *base = of_iomap(node, 0);

	of_node_clear_flag(node, OF_POPULATED);

	if (!base)
		return -ENXIO;

	versatile_sys_24mhz = base + SYS_24MHZ;

	sched_clock_register(versatile_sys_24mhz_read, 32, 24000000);

	return 0;
}
TIMER_OF_DECLARE(vexpress, "arm,vexpress-sysreg",
		       versatile_sched_clock_init);
TIMER_OF_DECLARE(versatile, "arm,versatile-sysreg",
		       versatile_sched_clock_init);
