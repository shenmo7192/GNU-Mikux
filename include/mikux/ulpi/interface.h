/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_ULPI_INTERFACE_H
#define __MIKUX_ULPI_INTERFACE_H

#include <mikux/types.h>

struct ulpi;
struct device;

/**
 * struct ulpi_ops - ULPI register access
 * @read: read operation for ULPI register access
 * @write: write operation for ULPI register access
 */
struct ulpi_ops {
	int (*read)(struct device *dev, u8 addr);
	int (*write)(struct device *dev, u8 addr, u8 val);
};

struct ulpi *ulpi_register_interface(struct device *, const struct ulpi_ops *);
void ulpi_unregister_interface(struct ulpi *);

#endif /* __MIKUX_ULPI_INTERFACE_H */
