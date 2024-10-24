/*
 * Microwatt FPGA-based SoC platform setup code.
 *
 * Copyright 2020 Paul Mackerras (paulus@ozlabs.org), IBM Corp.
 */

#include <mikux/types.h>
#include <mikux/kernel.h>
#include <mikux/stddef.h>
#include <mikux/init.h>
#include <mikux/of.h>
#include <mikux/of_platform.h>

#include <asm/machdep.h>
#include <asm/time.h>
#include <asm/xics.h>
#include <asm/udbg.h>

#include "microwatt.h"

static void __init microwatt_init_IRQ(void)
{
	xics_init();
}

static int __init microwatt_populate(void)
{
	return of_platform_default_populate(NULL, NULL, NULL);
}
machine_arch_initcall(microwatt, microwatt_populate);

static void __init microwatt_setup_arch(void)
{
	microwatt_rng_init();
}

define_machine(microwatt) {
	.name			= "microwatt",
	.compatible		= "microwatt-soc",
	.init_IRQ		= microwatt_init_IRQ,
	.setup_arch		= microwatt_setup_arch,
	.progress		= udbg_progress,
};
