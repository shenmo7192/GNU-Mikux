// SPDX-License-Identifier: GPL-2.0
/*
 * USB CDC Device Management subdriver
 *
 * Copyright (c) 2012  Bjørn Mork <bjorn@mork.no>
 */

#ifndef __MIKUX_USB_CDC_WDM_H
#define __MIKUX_USB_CDC_WDM_H

#include <mikux/wwan.h>
#include <uapi/mikux/usb/cdc-wdm.h>

extern struct usb_driver *usb_cdc_wdm_register(struct usb_interface *intf,
					struct usb_endpoint_descriptor *ep,
					int bufsize, enum wwan_port_type type,
					int (*manage_power)(struct usb_interface *, int));

#endif /* __MIKUX_USB_CDC_WDM_H */
