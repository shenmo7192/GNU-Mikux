/* SPDX-License-Identifier: GPL-2.0 */
/* atm.h - general ATM declarations */
#ifndef _MIKUX_ATM_H
#define _MIKUX_ATM_H

#include <uapi/mikux/atm.h>

#ifdef CONFIG_COMPAT
#include <mikux/compat.h>
struct compat_atmif_sioc {
	int number;
	int length;
	compat_uptr_t arg;
};
#endif
#endif
