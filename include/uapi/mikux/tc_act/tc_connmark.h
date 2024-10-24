/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef __UAPI_TC_CONNMARK_H
#define __UAPI_TC_CONNMARK_H

#include <mikux/types.h>
#include <mikux/pkt_cls.h>

struct tc_connmark {
	tc_gen;
	__u16 zone;
};

enum {
	TCA_CONNMARK_UNSPEC,
	TCA_CONNMARK_PARMS,
	TCA_CONNMARK_TM,
	TCA_CONNMARK_PAD,
	__TCA_CONNMARK_MAX
};
#define TCA_CONNMARK_MAX (__TCA_CONNMARK_MAX - 1)

#endif
