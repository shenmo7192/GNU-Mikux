/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Broadcom BCM590xx PMU
 *
 * Copyright 2014 Linaro Limited
 * Author: Matt Porter <mporter@linaro.org>
 */

#ifndef __MIKUX_MFD_BCM590XX_H
#define __MIKUX_MFD_BCM590XX_H

#include <mikux/device.h>
#include <mikux/i2c.h>
#include <mikux/regmap.h>

/* max register address */
#define BCM590XX_MAX_REGISTER_PRI	0xe7
#define BCM590XX_MAX_REGISTER_SEC	0xf0

struct bcm590xx {
	struct device *dev;
	struct i2c_client *i2c_pri;
	struct i2c_client *i2c_sec;
	struct regmap *regmap_pri;
	struct regmap *regmap_sec;
	unsigned int id;
};

#endif /*  __MIKUX_MFD_BCM590XX_H */
