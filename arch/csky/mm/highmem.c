// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microsystems co.,ltd.

#include <mikux/module.h>
#include <mikux/highmem.h>
#include <mikux/smp.h>
#include <mikux/memblock.h>
#include <asm/fixmap.h>
#include <asm/tlbflush.h>
#include <asm/cacheflush.h>

unsigned long highstart_pfn, highend_pfn;

void kmap_flush_tlb(unsigned long addr)
{
	flush_tlb_one(addr);
}
EXPORT_SYMBOL(kmap_flush_tlb);

void __init kmap_init(void)
{
	unsigned long vaddr;
	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t *pte;

	vaddr = PKMAP_BASE;
	fixrange_init(vaddr, vaddr + PAGE_SIZE*LAST_PKMAP, swapper_pg_dir);

	pgd = swapper_pg_dir + pgd_index(vaddr);
	pud = (pud_t *)pgd;
	pmd = pmd_offset(pud, vaddr);
	pte = pte_offset_kernel(pmd, vaddr);
	pkmap_page_table = pte;
}
