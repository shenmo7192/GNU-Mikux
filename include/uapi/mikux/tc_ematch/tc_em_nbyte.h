/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef __MIKUX_TC_EM_NBYTE_H
#define __MIKUX_TC_EM_NBYTE_H

#include <mikux/types.h>
#include <mikux/pkt_cls.h>

struct tcf_em_nbyte {
	__u16		off;
	__u16		len:12;
	__u8		layer:4;
};

#endif
