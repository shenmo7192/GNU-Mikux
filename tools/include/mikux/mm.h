/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _TOOLS_MIKUX_MM_H
#define _TOOLS_MIKUX_MM_H

#include <mikux/align.h>
#include <mikux/mmzone.h>

#define PAGE_SHIFT		12
#define PAGE_SIZE		(_AC(1, UL) << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE - 1))

#define PHYS_ADDR_MAX	(~(phys_addr_t)0)

#define PAGE_ALIGN(addr) ALIGN(addr, PAGE_SIZE)
#define PAGE_ALIGN_DOWN(addr) ALIGN_DOWN(addr, PAGE_SIZE)

#define __va(x) ((void *)((unsigned long)(x)))
#define __pa(x) ((unsigned long)(x))

#define pfn_to_page(pfn) ((void *)((pfn) * PAGE_SIZE))

#define phys_to_virt phys_to_virt
static inline void *phys_to_virt(unsigned long address)
{
	return __va(address);
}

#define virt_to_phys virt_to_phys
static inline phys_addr_t virt_to_phys(volatile void *address)
{
	return (phys_addr_t)address;
}

void reserve_bootmem_region(phys_addr_t start, phys_addr_t end, int nid);

static inline void totalram_pages_inc(void)
{
}

static inline void totalram_pages_add(long count)
{
}

static inline int early_pfn_to_nid(unsigned long pfn)
{
	return 0;
}

#endif
