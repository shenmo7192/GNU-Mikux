/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef __MIKUX_BRIDGE_EBT_PKTTYPE_H
#define __MIKUX_BRIDGE_EBT_PKTTYPE_H

#include <mikux/types.h>

struct ebt_pkttype_info {
	__u8 pkt_type;
	__u8 invert;
};
#define EBT_PKTTYPE_MATCH "pkttype"

#endif
