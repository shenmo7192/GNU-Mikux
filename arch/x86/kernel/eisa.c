// SPDX-License-Identifier: GPL-2.0-only
/*
 * EISA specific code
 */
#include <mikux/cc_platform.h>
#include <mikux/ioport.h>
#include <mikux/eisa.h>
#include <mikux/io.h>

#include <xen/xen.h>

static __init int eisa_bus_probe(void)
{
	u32 *p;

	if ((xen_pv_domain() && !xen_initial_domain()) || cc_platform_has(CC_ATTR_GUEST_SEV_SNP))
		return 0;

	p = memremap(0x0FFFD9, 4, MEMREMAP_WB);
	if (p && *p == 'E' + ('I' << 8) + ('S' << 16) + ('A' << 24))
		EISA_bus = 1;
	memunmap(p);
	return 0;
}
subsys_initcall(eisa_bus_probe);
