/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * include/mikux/irqchip/arm-gic-common.h
 *
 * Copyright (C) 2016 ARM Limited, All Rights Reserved.
 */
#ifndef __MIKUX_IRQCHIP_ARM_GIC_COMMON_H
#define __MIKUX_IRQCHIP_ARM_GIC_COMMON_H

#include <mikux/irqchip/arm-vgic-info.h>

#define GICD_INT_DEF_PRI		0xa0

struct irq_domain;
struct fwnode_handle;
int gicv2m_init(struct fwnode_handle *parent_handle,
		struct irq_domain *parent);

#endif /* __MIKUX_IRQCHIP_ARM_GIC_COMMON_H */
