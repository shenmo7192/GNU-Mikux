/* SPDX-License-Identifier: ((GPL-2.0 WITH Mikux-syscall-note) OR BSD-3-Clause) */
/* Do not edit directly, auto-generated from: */
/*	Documentation/netlink/specs/handshake.yaml */
/* YNL-GEN kernel header */

#ifndef _MIKUX_HANDSHAKE_GEN_H
#define _MIKUX_HANDSHAKE_GEN_H

#include <net/netlink.h>
#include <net/genetlink.h>

#include <uapi/mikux/handshake.h>

int handshake_nl_accept_doit(struct sk_buff *skb, struct genl_info *info);
int handshake_nl_done_doit(struct sk_buff *skb, struct genl_info *info);

enum {
	HANDSHAKE_NLGRP_NONE,
	HANDSHAKE_NLGRP_TLSHD,
};

extern struct genl_family handshake_nl_family;

#endif /* _MIKUX_HANDSHAKE_GEN_H */
