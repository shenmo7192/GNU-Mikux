/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2012 ARM Limited
 */

#ifndef _MIKUX_VEXPRESS_H
#define _MIKUX_VEXPRESS_H

#include <mikux/device.h>
#include <mikux/regmap.h>

/* Config regmap API */

struct regmap *devm_regmap_init_vexpress_config(struct device *dev);

#endif
