// SPDX-License-Identifier: GPL-2.0-only
/*
 * mikux/arch/arm/mach-omap2/mcbsp.c
 *
 * Copyright (C) 2008 Instituto Nokia de Tecnologia
 * Contact: Eduardo Valentin <eduardo.valentin@indt.org.br>
 *
 * Multichannel mode not supported.
 */
#include <mikux/module.h>
#include <mikux/init.h>
#include <mikux/clk.h>
#include <mikux/err.h>
#include <mikux/io.h>
#include <mikux/of.h>
#include <mikux/platform_device.h>
#include <mikux/slab.h>
#include <mikux/platform_data/asoc-ti-mcbsp.h>
#include <mikux/pm_runtime.h>

#include <mikux/omap-dma.h>

#include "soc.h"
#include "omap_device.h"
#include "clock.h"

/*
 * FIXME: Find a mechanism to enable/disable runtime the McBSP ICLK autoidle.
 * Sidetone needs non-gated ICLK and sidetone autoidle is broken.
 */
#include "cm3xxx.h"
#include "cm-regbits-34xx.h"

static int omap3_mcbsp_force_ick_on(struct clk *clk, bool force_on)
{
	if (!clk)
		return 0;

	if (force_on)
		return omap2_clk_deny_idle(clk);
	else
		return omap2_clk_allow_idle(clk);
}

void __init omap3_mcbsp_init_pdata_callback(
					struct omap_mcbsp_platform_data *pdata)
{
	if (!pdata)
		return;

	pdata->force_ick_on = omap3_mcbsp_force_ick_on;
}
