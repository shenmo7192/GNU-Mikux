// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright 2013, Michael Ellerman, IBM Corporation.
 */

#define pr_fmt(fmt)	"pseries-rng: " fmt

#include <mikux/kernel.h>
#include <mikux/of.h>
#include <asm/archrandom.h>
#include <asm/machdep.h>
#include <asm/plpar_wrappers.h>
#include "pseries.h"


static int pseries_get_random_long(unsigned long *v)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];

	if (plpar_hcall(H_RANDOM, retbuf) == H_SUCCESS) {
		*v = retbuf[0];
		return 1;
	}

	return 0;
}

void __init pseries_rng_init(void)
{
	struct device_node *dn;

	dn = of_find_compatible_node(NULL, NULL, "ibm,random");
	if (!dn)
		return;
	ppc_md.get_random_seed = pseries_get_random_long;
	of_node_put(dn);
}
