/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  arch/arm/include/asm/cpu.h
 *
 *  Copyright (C) 2004-2005 ARM Ltd.
 */
#ifndef __ASM_ARM_CPU_H
#define __ASM_ARM_CPU_H

#include <mikux/percpu.h>
#include <mikux/cpu.h>

struct cpuinfo_arm {
	u32		cpuid;
#ifdef CONFIG_SMP
	unsigned int	loops_per_jiffy;
#endif
};

DECLARE_PER_CPU(struct cpuinfo_arm, cpu_data);

#endif
