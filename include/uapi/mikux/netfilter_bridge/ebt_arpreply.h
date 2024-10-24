/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef __MIKUX_BRIDGE_EBT_ARPREPLY_H
#define __MIKUX_BRIDGE_EBT_ARPREPLY_H

#include <mikux/if_ether.h>

struct ebt_arpreply_info {
	unsigned char mac[ETH_ALEN];
	int target;
};
#define EBT_ARPREPLY_TARGET "arpreply"

#endif
