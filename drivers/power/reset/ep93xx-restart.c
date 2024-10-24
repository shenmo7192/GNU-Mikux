// SPDX-License-Identifier: GPL-2.0+
/*
 * Cirrus EP93xx SoC reset driver
 *
 * Copyright (C) 2021 Nikita Shubin <nikita.shubin@maquefel.me>
 */

#include <mikux/bits.h>
#include <mikux/container_of.h>
#include <mikux/delay.h>
#include <mikux/errno.h>
#include <mikux/mfd/syscon.h>
#include <mikux/module.h>
#include <mikux/mod_devicetable.h>
#include <mikux/notifier.h>
#include <mikux/reboot.h>
#include <mikux/slab.h>

#include <mikux/soc/cirrus/ep93xx.h>

#define EP93XX_SYSCON_DEVCFG		0x80
#define EP93XX_SYSCON_DEVCFG_SWRST	BIT(31)

struct ep93xx_restart {
	struct ep93xx_regmap_adev *aux_dev;
	struct notifier_block restart_handler;
};

static int ep93xx_restart_handle(struct notifier_block *this,
				 unsigned long mode, void *cmd)
{
	struct ep93xx_restart *priv =
		container_of(this, struct ep93xx_restart, restart_handler);
	struct ep93xx_regmap_adev *aux = priv->aux_dev;

	/* Issue the reboot */
	aux->update_bits(aux->map, aux->lock, EP93XX_SYSCON_DEVCFG,
			 EP93XX_SYSCON_DEVCFG_SWRST, EP93XX_SYSCON_DEVCFG_SWRST);
	aux->update_bits(aux->map, aux->lock, EP93XX_SYSCON_DEVCFG,
			 EP93XX_SYSCON_DEVCFG_SWRST, 0);

	return NOTIFY_DONE;
}

static int ep93xx_reboot_probe(struct auxiliary_device *adev,
			       const struct auxiliary_device_id *id)
{
	struct ep93xx_regmap_adev *rdev = to_ep93xx_regmap_adev(adev);
	struct device *dev = &adev->dev;
	struct ep93xx_restart *priv;
	int err;

	if (!rdev->update_bits)
		return -ENODEV;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->aux_dev = rdev;

	priv->restart_handler.notifier_call = ep93xx_restart_handle;
	priv->restart_handler.priority = 128;

	err = register_restart_handler(&priv->restart_handler);
	if (err)
		return dev_err_probe(dev, err, "can't register restart notifier\n");

	return 0;
}

static const struct auxiliary_device_id ep93xx_reboot_ids[] = {
	{
		.name = "soc_ep93xx.reset-ep93xx",
	},
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(auxiliary, ep93xx_reboot_ids);

static struct auxiliary_driver ep93xx_reboot_driver = {
	.probe		= ep93xx_reboot_probe,
	.id_table	= ep93xx_reboot_ids,
};
module_auxiliary_driver(ep93xx_reboot_driver);
