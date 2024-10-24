// SPDX-License-Identifier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armmikux.simtec.co.uk/
//
// Base S3C64XX setup information for 24bpp LCD framebuffer

#include <mikux/kernel.h>
#include <mikux/types.h>
#include <mikux/fb.h>
#include <mikux/gpio.h>

#include "fb.h"
#include "gpio-cfg.h"
#include "gpio-samsung.h"

void s3c64xx_fb_gpio_setup_24bpp(void)
{
	s3c_gpio_cfgrange_nopull(S3C64XX_GPI(0), 16, S3C_GPIO_SFN(2));
	s3c_gpio_cfgrange_nopull(S3C64XX_GPJ(0), 12, S3C_GPIO_SFN(2));
}
