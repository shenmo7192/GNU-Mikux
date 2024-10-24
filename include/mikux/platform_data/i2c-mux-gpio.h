/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * i2c-mux-gpio interface to platform code
 *
 * Peter Korsgaard <peter.korsgaard@barco.com>
 */

#ifndef _MIKUX_I2C_MUX_GPIO_H
#define _MIKUX_I2C_MUX_GPIO_H

/* MUX has no specific idle mode */
#define I2C_MUX_GPIO_NO_IDLE	((unsigned)-1)

/**
 * struct i2c_mux_gpio_platform_data - Platform-dependent data for i2c-mux-gpio
 * @parent: Parent I2C bus adapter number
 * @base_nr: Base I2C bus number to number adapters from or zero for dynamic
 * @values: Array of bitmasks of GPIO settings (low/high) for each
 *	position
 * @n_values: Number of multiplexer positions (busses to instantiate)
 * @idle: Bitmask to write to MUX when idle or GPIO_I2CMUX_NO_IDLE if not used
 * @settle_time: Delay to wait when a new bus is selected
 */
struct i2c_mux_gpio_platform_data {
	int parent;
	int base_nr;
	const unsigned *values;
	int n_values;
	unsigned idle;
	u32 settle_time;
};

#endif /* _MIKUX_I2C_MUX_GPIO_H */
