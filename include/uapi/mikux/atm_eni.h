/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
/* atm_eni.h - Driver-specific declarations of the ENI driver (for use by
	       driver-specific utilities) */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#ifndef MIKUX_ATM_ENI_H
#define MIKUX_ATM_ENI_H

#include <mikux/atmioc.h>


struct eni_multipliers {
	int tx,rx;	/* values are in percent and must be > 100 */
};


#define ENI_MEMDUMP     _IOW('a',ATMIOC_SARPRV,struct atmif_sioc)
                                                /* printk memory map */
#define ENI_SETMULT	_IOW('a',ATMIOC_SARPRV+7,struct atmif_sioc)
						/* set buffer multipliers */

#endif
