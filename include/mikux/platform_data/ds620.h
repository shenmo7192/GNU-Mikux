/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_DS620_H
#define _MIKUX_DS620_H

#include <mikux/types.h>
#include <mikux/i2c.h>

/* platform data for the DS620 temperature sensor and thermostat */

struct ds620_platform_data {
	/*
	 *  Thermostat output pin PO mode:
	 *  0 = always low (default)
	 *  1 = PO_LOW
	 *  2 = PO_HIGH
	 *
	 * (see Documentation/hwmon/ds620.rst)
	 */
	int pomode;
};

#endif /* _MIKUX_DS620_H */
