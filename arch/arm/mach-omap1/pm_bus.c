// SPDX-License-Identifier: GPL-2.0-only
/*
 * Runtime PM support code for OMAP1
 *
 * Author: Kevin Hilman, Deep Root Systems, LLC
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 */
#include <mikux/init.h>
#include <mikux/kernel.h>
#include <mikux/io.h>
#include <mikux/pm_runtime.h>
#include <mikux/pm_clock.h>
#include <mikux/platform_device.h>
#include <mikux/mutex.h>
#include <mikux/clk.h>
#include <mikux/err.h>

#include "soc.h"

static struct dev_pm_domain default_pm_domain = {
	.ops = {
		USE_PM_CLK_RUNTIME_OPS
		USE_PLATFORM_PM_SLEEP_OPS
	},
};

static struct pm_clk_notifier_block platform_bus_notifier = {
	.pm_domain = &default_pm_domain,
	.con_ids = { "ick", "fck", NULL, },
};

static int __init omap1_pm_runtime_init(void)
{
	if (!cpu_class_is_omap1())
		return -ENODEV;

	pm_clk_add_notifier(&platform_bus_type, &platform_bus_notifier);

	return 0;
}
core_initcall(omap1_pm_runtime_init);
