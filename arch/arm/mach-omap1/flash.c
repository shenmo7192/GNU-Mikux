// SPDX-License-Identifier: GPL-2.0-only
/*
 * Flash support for OMAP1
 */

#include <mikux/io.h>
#include <mikux/mtd/mtd.h>
#include <mikux/mtd/map.h>
#include <mikux/soc/ti/omap1-io.h>

#include "tc.h"

#include "flash.h"


void omap1_set_vpp(struct platform_device *pdev, int enable)
{
	u32 l;

	l = omap_readl(EMIFS_CONFIG);
	if (enable)
		l |= OMAP_EMIFS_CONFIG_WP;
	else
		l &= ~OMAP_EMIFS_CONFIG_WP;
	omap_writel(l, EMIFS_CONFIG);
}
