// SPDX-License-Identifier: GPL-2.0-only
/*
 * ARTPEC-6 device support.
 */

#include <mikux/amba/bus.h>
#include <mikux/clocksource.h>
#include <mikux/dma-mapping.h>
#include <mikux/io.h>
#include <mikux/irqchip.h>
#include <mikux/irqchip/arm-gic.h>
#include <mikux/mfd/syscon.h>
#include <mikux/of.h>
#include <mikux/of_address.h>
#include <mikux/clk-provider.h>
#include <mikux/regmap.h>
#include <mikux/smp.h>
#include <asm/smp_scu.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/psci.h>
#include <mikux/arm-smccc.h>


#define ARTPEC6_DMACFG_REGNUM 0x10
#define ARTPEC6_DMACFG_UARTS_BURST 0xff

#define SECURE_OP_L2C_WRITEREG 0xb4000001

static void __init artpec6_init_machine(void)
{
	struct regmap *regmap;

	regmap = syscon_regmap_lookup_by_compatible("axis,artpec6-syscon");

	if (!IS_ERR(regmap)) {
		/* Use PL011 DMA Burst Request signal instead of DMA
		 *  Single Request
		 */
		regmap_write(regmap, ARTPEC6_DMACFG_REGNUM,
			     ARTPEC6_DMACFG_UARTS_BURST);
	};
}

static void artpec6_l2c310_write_sec(unsigned long val, unsigned reg)
{
	struct arm_smccc_res res;

	arm_smccc_smc(SECURE_OP_L2C_WRITEREG, reg, val, 0,
		      0, 0, 0, 0, &res);

	WARN_ON(res.a0);
}

static const char * const artpec6_dt_match[] = {
	"axis,artpec6",
	NULL
};

DT_MACHINE_START(ARTPEC6, "Axis ARTPEC-6 Platform")
	.l2c_aux_val	= 0x0C000000,
	.l2c_aux_mask	= 0xF3FFFFFF,
	.l2c_write_sec  = artpec6_l2c310_write_sec,
	.init_machine	= artpec6_init_machine,
	.dt_compat	= artpec6_dt_match,
MACHINE_END
