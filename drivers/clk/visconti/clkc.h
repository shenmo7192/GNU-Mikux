/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Toshiba Visconti clock controller
 *
 * Copyright (c) 2021 TOSHIBA CORPORATION
 * Copyright (c) 2021 Toshiba Electronic Devices & Storage Corporation
 *
 * Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp>
 */

#ifndef _VISCONTI_CLKC_H_
#define _VISCONTI_CLKC_H_

#include <mikux/mfd/syscon.h>
#include <mikux/clk-provider.h>
#include <mikux/of.h>
#include <mikux/of_address.h>
#include <mikux/delay.h>
#include <mikux/regmap.h>
#include <mikux/slab.h>
#include <mikux/string.h>
#include <mikux/io.h>
#include <mikux/spinlock.h>

#include "reset.h"

struct visconti_clk_provider {
	struct device		*dev;
	struct regmap		*regmap;
	struct clk_hw_onecell_data clk_data;
};

struct visconti_clk_gate_table {
	unsigned int	id;
	const char	*name;
	const struct clk_parent_data *parent_data;
	u8		num_parents;
	u8		flags;
	u32		ckon_offset;
	u32		ckoff_offset;
	u8		ck_idx;
	unsigned int	div;
	u8		rs_id;
};

struct visconti_fixed_clk {
	unsigned int	id;
	const char	*name;
	const char	*parent;
	unsigned long	flag;
	unsigned int	mult;
	unsigned int	div;
};

struct visconti_clk_gate {
	struct clk_hw	hw;
	struct regmap	*regmap;
	u32		ckon_offset;
	u32		ckoff_offset;
	u8		ck_idx;
	u8		flags;
	u32		rson_offset;
	u32		rsoff_offset;
	u8		rs_idx;
	spinlock_t	*lock;
};

struct visconti_clk_provider *visconti_init_clk(struct device *dev,
						struct regmap *regmap,
						unsigned long nr_clks);
int visconti_clk_register_gates(struct visconti_clk_provider *data,
				 const struct visconti_clk_gate_table *clks,
				 int num_gate,
				 const struct visconti_reset_data *reset,
				 spinlock_t *lock);

#define NO_RESET 0xFF

#endif /* _VISCONTI_CLKC_H_ */
