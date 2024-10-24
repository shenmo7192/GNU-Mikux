// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2005 Dmitry Torokhov
 */

#ifndef __MIKUX_USB_INPUT_H
#define __MIKUX_USB_INPUT_H

#include <mikux/usb.h>
#include <mikux/input.h>
#include <asm/byteorder.h>

static inline void
usb_to_input_id(const struct usb_device *dev, struct input_id *id)
{
	id->bustype = BUS_USB;
	id->vendor = le16_to_cpu(dev->descriptor.idVendor);
	id->product = le16_to_cpu(dev->descriptor.idProduct);
	id->version = le16_to_cpu(dev->descriptor.bcdDevice);
}

#endif /* __MIKUX_USB_INPUT_H */
