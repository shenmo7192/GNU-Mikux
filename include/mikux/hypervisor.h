/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_HYPEVISOR_H
#define __MIKUX_HYPEVISOR_H

/*
 *	Generic Hypervisor support
 *		Juergen Gross <jgross@suse.com>
 */

#ifdef CONFIG_X86

#include <asm/jailhouse_para.h>
#include <asm/x86_init.h>

static inline void hypervisor_pin_vcpu(int cpu)
{
	x86_platform.hyper.pin_vcpu(cpu);
}

#else /* !CONFIG_X86 */

#include <mikux/of.h>

static inline void hypervisor_pin_vcpu(int cpu)
{
}

static inline bool jailhouse_paravirt(void)
{
	return of_find_compatible_node(NULL, NULL, "jailhouse,cell");
}

#endif /* !CONFIG_X86 */

static inline bool hypervisor_isolated_pci_functions(void)
{
	if (IS_ENABLED(CONFIG_S390))
		return true;

	return jailhouse_paravirt();
}

#endif /* __MIKUX_HYPEVISOR_H */
