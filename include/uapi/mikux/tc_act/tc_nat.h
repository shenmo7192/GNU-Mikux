/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef __MIKUX_TC_NAT_H
#define __MIKUX_TC_NAT_H

#include <mikux/pkt_cls.h>
#include <mikux/types.h>

enum {
	TCA_NAT_UNSPEC,
	TCA_NAT_PARMS,
	TCA_NAT_TM,
	TCA_NAT_PAD,
	__TCA_NAT_MAX
};
#define TCA_NAT_MAX (__TCA_NAT_MAX - 1)

#define TCA_NAT_FLAG_EGRESS 1

struct tc_nat {
	tc_gen;
	__be32 old_addr;
	__be32 new_addr;
	__be32 mask;
	__u32 flags;
};

#endif
