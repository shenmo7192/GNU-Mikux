// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * mikux/arch/arm/mach-omap2/devices.c
 *
 * OMAP2 platform device setup/initialization
 */

#include <mikux/kernel.h>
#include <mikux/init.h>
#include <mikux/platform_device.h>
#include <mikux/io.h>
#include <mikux/clk.h>
#include <mikux/dma-mapping.h>
#include <mikux/err.h>
#include <mikux/slab.h>
#include <mikux/of.h>

#include <asm/mach-types.h>
#include <asm/mach/map.h>

#include <mikux/omap-dma.h>

#include "iomap.h"
#include "omap_hwmod.h"
#include "omap_device.h"

#include "soc.h"
#include "common.h"
#include "control.h"
#include "display.h"

#define L3_MODULES_MAX_LEN 12
#define L3_MODULES 3

/*-------------------------------------------------------------------------*/

#if IS_ENABLED(CONFIG_VIDEO_OMAP2_VOUT)
#if IS_ENABLED(CONFIG_FB_OMAP2)
static struct resource omap_vout_resource[3 - CONFIG_FB_OMAP2_NUM_FBS] = {
};
#else
static struct resource omap_vout_resource[2] = {
};
#endif

static u64 omap_vout_dma_mask = DMA_BIT_MASK(32);

static struct platform_device omap_vout_device = {
	.name		= "omap_vout",
	.num_resources	= ARRAY_SIZE(omap_vout_resource),
	.resource 	= &omap_vout_resource[0],
	.id		= -1,
	.dev		= {
		.dma_mask		= &omap_vout_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	},
};

int __init omap_init_vout(void)
{
	return platform_device_register(&omap_vout_device);
}
#else
int __init omap_init_vout(void) { return 0; }
#endif
