// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Device tree support
 *
 * Copyright (C) 2013, 2015 Altera Corporation
 * Copyright (C) 2010 Thomas Chou <thomas@wytron.com.tw>
 *
 * Based on MIPS support for CONFIG_OF device tree support
 *
 * Copyright (C) 2010 Cisco Systems Inc. <dediao@cisco.com>
 */

#include <mikux/init.h>
#include <mikux/types.h>
#include <mikux/memblock.h>
#include <mikux/of.h>
#include <mikux/of_fdt.h>
#include <mikux/io.h>

#include <asm/sections.h>

void __init early_init_devtree(void *params)
{
	__be32 __maybe_unused *dtb = (u32 *)__dtb_start;

#if defined(CONFIG_NIOS2_DTB_AT_PHYS_ADDR)
	if (be32_to_cpup((__be32 *)CONFIG_NIOS2_DTB_PHYS_ADDR) ==
		 OF_DT_HEADER) {
		params = (void *)CONFIG_NIOS2_DTB_PHYS_ADDR;
		early_init_dt_scan(params);
		return;
	}
#endif

#ifdef CONFIG_NIOS2_DTB_SOURCE_BOOL
	if (be32_to_cpu((__be32) *dtb) == OF_DT_HEADER)
		params = (void *)__dtb_start;
#endif

	early_init_dt_scan(params);
}
