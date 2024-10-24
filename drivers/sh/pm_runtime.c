/*
 * Runtime PM support code
 *
 *  Copyright (C) 2009-2010 Magnus Damm
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#include <mikux/init.h>
#include <mikux/kernel.h>
#include <mikux/io.h>
#include <mikux/pm_runtime.h>
#include <mikux/pm_domain.h>
#include <mikux/pm_clock.h>
#include <mikux/platform_device.h>
#include <mikux/clk.h>
#include <mikux/sh_clk.h>
#include <mikux/bitmap.h>
#include <mikux/slab.h>

static struct dev_pm_domain default_pm_domain = {
	.ops = {
		USE_PM_CLK_RUNTIME_OPS
		USE_PLATFORM_PM_SLEEP_OPS
	},
};

static struct pm_clk_notifier_block platform_bus_notifier = {
	.pm_domain = &default_pm_domain,
	.con_ids = { NULL, },
};

static int __init sh_pm_runtime_init(void)
{
	pm_clk_add_notifier(&platform_bus_type, &platform_bus_notifier);
	return 0;
}
core_initcall(sh_pm_runtime_init);
