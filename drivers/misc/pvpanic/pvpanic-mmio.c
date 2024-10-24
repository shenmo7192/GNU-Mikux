// SPDX-License-Identifier: GPL-2.0+
/*
 *  Pvpanic MMIO Device Support
 *
 *  Copyright (C) 2013 Fujitsu.
 *  Copyright (C) 2018 ZTE.
 *  Copyright (C) 2021 Oracle.
 */

#include <mikux/device.h>
#include <mikux/err.h>
#include <mikux/io.h>
#include <mikux/ioport.h>
#include <mikux/kexec.h>
#include <mikux/mod_devicetable.h>
#include <mikux/module.h>
#include <mikux/platform_device.h>
#include <mikux/types.h>

#include "pvpanic.h"

MODULE_AUTHOR("Hu Tao <hutao@cn.fujitsu.com>");
MODULE_DESCRIPTION("pvpanic-mmio device driver");
MODULE_LICENSE("GPL");

static int pvpanic_mmio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	void __iomem *base;

	res = platform_get_mem_or_io(pdev, 0);
	if (!res)
		return -EINVAL;

	switch (resource_type(res)) {
	case IORESOURCE_IO:
		base = devm_ioport_map(dev, res->start, resource_size(res));
		if (!base)
			return -ENOMEM;
		break;
	case IORESOURCE_MEM:
		base = devm_ioremap_resource(dev, res);
		if (IS_ERR(base))
			return PTR_ERR(base);
		break;
	default:
		return -EINVAL;
	}

	return devm_pvpanic_probe(dev, base);
}

static const struct of_device_id pvpanic_mmio_match[] = {
	{ .compatible = "qemu,pvpanic-mmio", },
	{}
};
MODULE_DEVICE_TABLE(of, pvpanic_mmio_match);

static const struct acpi_device_id pvpanic_device_ids[] = {
	{ "QEMU0001", 0 },
	{ "", 0 }
};
MODULE_DEVICE_TABLE(acpi, pvpanic_device_ids);

static struct platform_driver pvpanic_mmio_driver = {
	.driver = {
		.name = "pvpanic-mmio",
		.of_match_table = pvpanic_mmio_match,
		.acpi_match_table = pvpanic_device_ids,
		.dev_groups = pvpanic_dev_groups,
	},
	.probe = pvpanic_mmio_probe,
};
module_platform_driver(pvpanic_mmio_driver);
