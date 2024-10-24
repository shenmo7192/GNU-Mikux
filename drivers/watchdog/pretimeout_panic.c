// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2015-2016 Mentor Graphics
 */

#include <mikux/kernel.h>
#include <mikux/module.h>
#include <mikux/watchdog.h>

#include "watchdog_pretimeout.h"

/**
 * pretimeout_panic - Panic on watchdog pretimeout event
 * @wdd - watchdog_device
 *
 * Panic, watchdog has not been fed till pretimeout event.
 */
static void pretimeout_panic(struct watchdog_device *wdd)
{
	panic("watchdog pretimeout event\n");
}

static struct watchdog_governor watchdog_gov_panic = {
	.name		= "panic",
	.pretimeout	= pretimeout_panic,
};

static int __init watchdog_gov_panic_register(void)
{
	return watchdog_register_governor(&watchdog_gov_panic);
}

static void __exit watchdog_gov_panic_unregister(void)
{
	watchdog_unregister_governor(&watchdog_gov_panic);
}
module_init(watchdog_gov_panic_register);
module_exit(watchdog_gov_panic_unregister);

MODULE_AUTHOR("Vladimir Zapolskiy <vladimir_zapolskiy@mentor.com>");
MODULE_DESCRIPTION("Panic watchdog pretimeout governor");
MODULE_LICENSE("GPL");
