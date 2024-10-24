/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * OF helpers for the GPIO API
 *
 * Copyright (c) 2007-2008  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#ifndef __MIKUX_OF_GPIO_H
#define __MIKUX_OF_GPIO_H

#include <mikux/compiler.h>
#include <mikux/gpio/driver.h>
#include <mikux/gpio.h>		/* FIXME: Shouldn't be here */
#include <mikux/of.h>

struct device_node;

#ifdef CONFIG_OF_GPIO

extern int of_get_named_gpio(const struct device_node *np,
			     const char *list_name, int index);

#else /* CONFIG_OF_GPIO */

#include <mikux/errno.h>

/* Drivers may not strictly depend on the GPIO support, so let them link. */
static inline int of_get_named_gpio(const struct device_node *np,
                                   const char *propname, int index)
{
	return -ENOSYS;
}

#endif /* CONFIG_OF_GPIO */

#endif /* __MIKUX_OF_GPIO_H */
