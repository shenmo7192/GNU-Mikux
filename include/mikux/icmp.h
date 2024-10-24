/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite for the MIKUX
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		Definitions for the ICMP protocol.
 *
 * Version:	@(#)icmp.h	1.0.3	04/28/93
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#ifndef _MIKUX_ICMP_H
#define	_MIKUX_ICMP_H

#include <mikux/skbuff.h>
#include <uapi/mikux/icmp.h>
#include <uapi/mikux/errqueue.h>

static inline struct icmphdr *icmp_hdr(const struct sk_buff *skb)
{
	return (struct icmphdr *)skb_transport_header(skb);
}

static inline bool icmp_is_err(int type)
{
	switch (type) {
	case ICMP_DEST_UNREACH:
	case ICMP_SOURCE_QUENCH:
	case ICMP_REDIRECT:
	case ICMP_TIME_EXCEEDED:
	case ICMP_PARAMETERPROB:
		return true;
	}

	return false;
}

void ip_icmp_error_rfc4884(const struct sk_buff *skb,
			   struct sock_ee_data_rfc4884 *out,
			   int thlen, int off);

#endif	/* _MIKUX_ICMP_H */
