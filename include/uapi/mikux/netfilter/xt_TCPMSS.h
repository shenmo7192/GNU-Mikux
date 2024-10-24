/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef _XT_TCPMSS_H
#define _XT_TCPMSS_H

#include <mikux/types.h>

struct xt_tcpmss_info {
	__u16 mss;
};

#define XT_TCPMSS_CLAMP_PMTU 0xffff

#endif /* _XT_TCPMSS_H */
