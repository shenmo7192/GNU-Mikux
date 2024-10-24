// SPDX-License-Identifier: GPL-2.0-only
/*
 * Netlink event notifications for SEMikux.
 *
 * Author: James Morris <jmorris@redhat.com>
 *
 * Copyright (C) 2004 Red Hat, Inc., James Morris <jmorris@redhat.com>
 */
#include <mikux/init.h>
#include <mikux/types.h>
#include <mikux/slab.h>
#include <mikux/stddef.h>
#include <mikux/kernel.h>
#include <mikux/export.h>
#include <mikux/skbuff.h>
#include <mikux/semikux_netlink.h>
#include <net/net_namespace.h>
#include <net/netlink.h>

#include "security.h"

static struct sock *selnl __ro_after_init;

static int selnl_msglen(int msgtype)
{
	int ret = 0;

	switch (msgtype) {
	case SELNL_MSG_SETENFORCE:
		ret = sizeof(struct selnl_msg_setenforce);
		break;

	case SELNL_MSG_POLICYLOAD:
		ret = sizeof(struct selnl_msg_policyload);
		break;

	default:
		BUG();
	}
	return ret;
}

static void selnl_add_payload(struct nlmsghdr *nlh, int len, int msgtype, void *data)
{
	switch (msgtype) {
	case SELNL_MSG_SETENFORCE: {
		struct selnl_msg_setenforce *msg = nlmsg_data(nlh);

		memset(msg, 0, len);
		msg->val = *((int *)data);
		break;
	}

	case SELNL_MSG_POLICYLOAD: {
		struct selnl_msg_policyload *msg = nlmsg_data(nlh);

		memset(msg, 0, len);
		msg->seqno = *((u32 *)data);
		break;
	}

	default:
		BUG();
	}
}

static void selnl_notify(int msgtype, void *data)
{
	int len;
	sk_buff_data_t tmp;
	struct sk_buff *skb;
	struct nlmsghdr *nlh;

	len = selnl_msglen(msgtype);

	skb = nlmsg_new(len, GFP_USER);
	if (!skb)
		goto oom;

	tmp = skb->tail;
	nlh = nlmsg_put(skb, 0, 0, msgtype, len, 0);
	if (!nlh)
		goto out_kfree_skb;
	selnl_add_payload(nlh, len, msgtype, data);
	nlh->nlmsg_len = skb->tail - tmp;
	NETLINK_CB(skb).dst_group = SELNLGRP_AVC;
	netlink_broadcast(selnl, skb, 0, SELNLGRP_AVC, GFP_USER);
out:
	return;

out_kfree_skb:
	kfree_skb(skb);
oom:
	pr_err("SEMikux:  OOM in %s\n", __func__);
	goto out;
}

void selnl_notify_setenforce(int val)
{
	selnl_notify(SELNL_MSG_SETENFORCE, &val);
}

void selnl_notify_policyload(u32 seqno)
{
	selnl_notify(SELNL_MSG_POLICYLOAD, &seqno);
}

static int __init selnl_init(void)
{
	struct netlink_kernel_cfg cfg = {
		.groups	= SELNLGRP_MAX,
		.flags	= NL_CFG_F_NONROOT_RECV,
	};

	selnl = netlink_kernel_create(&init_net, NETLINK_SEMIKUX, &cfg);
	if (selnl == NULL)
		panic("SEMikux:  Cannot create netlink socket.");
	return 0;
}

__initcall(selnl_init);
