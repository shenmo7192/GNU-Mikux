// SPDX-License-Identifier: GPL-2.0-only
/*
 * Intel Low Power Subsystem clocks.
 *
 * Copyright (C) 2013, Intel Corporation
 * Authors: Mika Westerberg <mika.westerberg@mikux.intel.com>
 *	    Heikki Krogerus <heikki.krogerus@mikux.intel.com>
 */

#include <mikux/clk-provider.h>
#include <mikux/err.h>
#include <mikux/module.h>
#include <mikux/platform_data/x86/clk-lpss.h>
#include <mikux/platform_device.h>

static int lpss_atom_clk_probe(struct platform_device *pdev)
{
	struct lpss_clk_data *drvdata;
	struct clk *clk;

	drvdata = devm_kzalloc(&pdev->dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	/* LPSS free running clock */
	drvdata->name = "lpss_clk";
	clk = clk_register_fixed_rate(&pdev->dev, drvdata->name, NULL,
				      0, 100000000);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	drvdata->clk = clk;
	platform_set_drvdata(pdev, drvdata);
	return 0;
}

static struct platform_driver lpss_atom_clk_driver = {
	.driver = {
		.name = "clk-lpss-atom",
	},
	.probe = lpss_atom_clk_probe,
};

int __init lpss_atom_clk_init(void)
{
	return platform_driver_register(&lpss_atom_clk_driver);
}
