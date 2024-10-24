// SPDX-License-Identifier: GPL-2.0
#include <mikux/compiler.h>
#include <mikux/init.h>
#include <mikux/export.h>
#include <mikux/highmem.h>
#include <mikux/sched.h>
#include <mikux/smp.h>
#include <asm/fixmap.h>
#include <asm/tlbflush.h>

unsigned long highstart_pfn, highend_pfn;

void kmap_flush_tlb(unsigned long addr)
{
	flush_tlb_one(addr);
}
EXPORT_SYMBOL(kmap_flush_tlb);
