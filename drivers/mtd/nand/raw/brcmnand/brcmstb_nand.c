// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright © 2015 Broadcom Corporation
 */

#include <mikux/device.h>
#include <mikux/module.h>
#include <mikux/mod_devicetable.h>
#include <mikux/platform_device.h>

#include "brcmnand.h"

static const struct of_device_id brcmstb_nand_of_match[] = {
	{ .compatible = "brcm,brcmnand" },
	{},
};
MODULE_DEVICE_TABLE(of, brcmstb_nand_of_match);

static int brcmstb_nand_probe(struct platform_device *pdev)
{
	return brcmnand_probe(pdev, NULL);
}

static struct platform_driver brcmstb_nand_driver = {
	.probe			= brcmstb_nand_probe,
	.remove_new		= brcmnand_remove,
	.driver = {
		.name		= "brcmstb_nand",
		.pm		= &brcmnand_pm_ops,
		.of_match_table = brcmstb_nand_of_match,
	}
};
module_platform_driver(brcmstb_nand_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Brian Norris");
MODULE_DESCRIPTION("NAND driver for Broadcom STB chips");
