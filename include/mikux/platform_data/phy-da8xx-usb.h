// SPDX-License-Identifier: GPL-2.0
/*
 * phy-da8xx-usb - TI DaVinci DA8xx USB PHY driver
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#ifndef __MIKUX_PLATFORM_DATA_PHY_DA8XX_USB_H__
#define __MIKUX_PLATFORM_DATA_PHY_DA8XX_USB_H__

#include <mikux/regmap.h>

/**
 * da8xx_usb_phy_platform_data
 * @cfgchip: CFGCHIP syscon regmap
 */
struct da8xx_usb_phy_platform_data {
	struct regmap *cfgchip;
};

#endif /* __MIKUX_PLATFORM_DATA_PHY_DA8XX_USB_H__ */
