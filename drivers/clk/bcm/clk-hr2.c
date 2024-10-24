// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2017 Broadcom

#include <mikux/kernel.h>
#include <mikux/err.h>
#include <mikux/clk-provider.h>
#include <mikux/io.h>
#include <mikux/of.h>
#include <mikux/of_address.h>

#include "clk-iproc.h"

static void __init hr2_armpll_init(struct device_node *node)
{
	iproc_armpll_setup(node);
}
CLK_OF_DECLARE(hr2_armpll, "brcm,hr2-armpll", hr2_armpll_init);
