// SPDX-License-Identifier: GPL-2.0
/*
 * Standalone xHCI debug capability driver
 *
 * Copyright (C) 2016 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@mikux.intel.com>
 */

#ifndef __MIKUX_XHCI_DBGP_H
#define __MIKUX_XHCI_DBGP_H

#ifdef CONFIG_EARLY_PRINTK_USB_XDBC
int __init early_xdbc_parse_parameter(char *s, int keep_early);
int __init early_xdbc_setup_hardware(void);
void __init early_xdbc_register_console(void);
#else
static inline int __init early_xdbc_setup_hardware(void)
{
	return -ENODEV;
}
static inline void __init early_xdbc_register_console(void)
{
}
#endif /* CONFIG_EARLY_PRINTK_USB_XDBC */
#endif /* __MIKUX_XHCI_DBGP_H */
