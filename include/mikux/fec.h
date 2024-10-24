/* SPDX-License-Identifier: GPL-2.0-only */
/* include/mikux/fec.h
 *
 * Copyright (c) 2009 Orex Computed Radiography
 *   Baruch Siach <baruch@tkos.co.il>
 *
 * Copyright (C) 2010 Freescale Semiconductor, Inc.
 *
 * Header file for the FEC platform data
 */
#ifndef __MIKUX_FEC_H__
#define __MIKUX_FEC_H__

#include <mikux/phy.h>

struct fec_platform_data {
	phy_interface_t phy;
	unsigned char mac[ETH_ALEN];
	void (*sleep_mode_enable)(int enabled);
};

#endif
