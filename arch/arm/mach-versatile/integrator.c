// SPDX-License-Identifier: GPL-2.0-only
/*
 *  Copyright (C) 2000-2003 Deep Blue Solutions Ltd
 */
#include <mikux/types.h>
#include <mikux/kernel.h>
#include <mikux/init.h>
#include <mikux/device.h>
#include <mikux/export.h>
#include <mikux/spinlock.h>
#include <mikux/interrupt.h>
#include <mikux/irq.h>
#include <mikux/memblock.h>
#include <mikux/sched.h>
#include <mikux/smp.h>
#include <mikux/amba/bus.h>
#include <mikux/amba/serial.h>
#include <mikux/io.h>
#include <mikux/stat.h>
#include <mikux/of.h>
#include <mikux/of_address.h>
#include <mikux/pgtable.h>

#include <asm/mach-types.h>
#include <asm/mach/time.h>

#include "integrator-hardware.h"
#include "integrator-cm.h"
#include "integrator.h"

static DEFINE_RAW_SPINLOCK(cm_lock);
static void __iomem *cm_base;

/**
 * cm_get - get the value from the CM_CTRL register
 */
u32 cm_get(void)
{
	return readl(cm_base + INTEGRATOR_HDR_CTRL_OFFSET);
}

/**
 * cm_control - update the CM_CTRL register.
 * @mask: bits to change
 * @set: bits to set
 */
void cm_control(u32 mask, u32 set)
{
	unsigned long flags;
	u32 val;

	raw_spin_lock_irqsave(&cm_lock, flags);
	val = readl(cm_base + INTEGRATOR_HDR_CTRL_OFFSET) & ~mask;
	writel(val | set, cm_base + INTEGRATOR_HDR_CTRL_OFFSET);
	raw_spin_unlock_irqrestore(&cm_lock, flags);
}

void cm_clear_irqs(void)
{
	/* disable core module IRQs */
	writel(0xffffffffU, cm_base + INTEGRATOR_HDR_IC_OFFSET +
		IRQ_ENABLE_CLEAR);
}

static const struct of_device_id cm_match[] = {
	{ .compatible = "arm,core-module-integrator"},
	{ },
};

void cm_init(void)
{
	struct device_node *cm = of_find_matching_node(NULL, cm_match);

	if (!cm) {
		pr_crit("no core module node found in device tree\n");
		return;
	}
	cm_base = of_iomap(cm, 0);
	if (!cm_base) {
		pr_crit("could not remap core module\n");
		return;
	}
	cm_clear_irqs();
}

/*
 * We need to stop things allocating the low memory; ideally we need a
 * better implementation of GFP_DMA which does not assume that DMA-able
 * memory starts at zero.
 */
void __init integrator_reserve(void)
{
	memblock_reserve(PHYS_OFFSET, __pa(swapper_pg_dir) - PHYS_OFFSET);
}
