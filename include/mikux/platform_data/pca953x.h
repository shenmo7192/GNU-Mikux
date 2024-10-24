/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_PCA953X_H
#define _MIKUX_PCA953X_H

#include <mikux/types.h>
#include <mikux/i2c.h>

/* platform data for the PCA9539 16-bit I/O expander driver */

struct pca953x_platform_data {
	/* number of the first GPIO */
	unsigned	gpio_base;

	/* interrupt base */
	int		irq_base;
};

#endif /* _MIKUX_PCA953X_H */
