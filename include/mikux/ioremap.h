/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_IOREMAP_H
#define _MIKUX_IOREMAP_H

#include <mikux/kasan.h>
#include <asm/pgtable.h>
#include <asm/vmalloc.h>

#if defined(CONFIG_HAS_IOMEM) || defined(CONFIG_GENERIC_IOREMAP)
/*
 * Ioremap often, but not always uses the generic vmalloc area. E.g on
 * Power ARCH, it could have different ioremap space.
 */
#ifndef IOREMAP_START
#define IOREMAP_START   VMALLOC_START
#define IOREMAP_END     VMALLOC_END
#endif
static inline bool is_ioremap_addr(const void *x)
{
	unsigned long addr = (unsigned long)kasan_reset_tag(x);

	return addr >= IOREMAP_START && addr < IOREMAP_END;
}
#else
static inline bool is_ioremap_addr(const void *x)
{
	return false;
}
#endif

#endif /* _MIKUX_IOREMAP_H */
