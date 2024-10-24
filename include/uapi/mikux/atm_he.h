/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
/* atm_he.h */

#ifndef MIKUX_ATM_HE_H
#define MIKUX_ATM_HE_H

#include <mikux/atmioc.h>

#define HE_GET_REG	_IOW('a', ATMIOC_SARPRV, struct atmif_sioc)

#define HE_REGTYPE_PCI	1
#define HE_REGTYPE_RCM	2
#define HE_REGTYPE_TCM	3
#define HE_REGTYPE_MBOX	4

struct he_ioctl_reg {
	unsigned addr, val;
	char type;
};

#endif /* MIKUX_ATM_HE_H */
