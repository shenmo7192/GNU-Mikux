/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_PLATFORM_DATA_BCMGENET_H__
#define __MIKUX_PLATFORM_DATA_BCMGENET_H__

#include <mikux/types.h>
#include <mikux/if_ether.h>
#include <mikux/phy.h>

struct bcmgenet_platform_data {
	bool		mdio_enabled;
	phy_interface_t	phy_interface;
	int		phy_address;
	int		phy_speed;
	int		phy_duplex;
	u8		mac_address[ETH_ALEN];
	int		genet_version;
};

#endif
