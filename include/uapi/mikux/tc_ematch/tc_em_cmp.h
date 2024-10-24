/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef __MIKUX_TC_EM_CMP_H
#define __MIKUX_TC_EM_CMP_H

#include <mikux/types.h>
#include <mikux/pkt_cls.h>

struct tcf_em_cmp {
	__u32		val;
	__u32		mask;
	__u16		off;
	__u8		align:4;
	__u8		flags:4;
	__u8		layer:4;
	__u8		opnd:4;
};

enum {
	TCF_EM_ALIGN_U8  = 1,
	TCF_EM_ALIGN_U16 = 2,
	TCF_EM_ALIGN_U32 = 4
};

#define TCF_EM_CMP_TRANS	1

#endif
