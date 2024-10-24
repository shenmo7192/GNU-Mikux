// SPDX-License-Identifier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armmikux.simtec.co.uk/
//
// Base S3C64XX I2C bus 0 gpio configuration

#include <mikux/kernel.h>
#include <mikux/types.h>
#include <mikux/gpio.h>

struct platform_device; /* don't need the contents */

#include <mikux/platform_data/i2c-s3c2410.h>
#include "gpio-cfg.h"
#include "gpio-samsung.h"

void s3c_i2c0_cfg_gpio(struct platform_device *dev)
{
	s3c_gpio_cfgall_range(S3C64XX_GPB(5), 2,
			      S3C_GPIO_SFN(2), S3C_GPIO_PULL_UP);
}
