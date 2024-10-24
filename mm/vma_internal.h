/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * vma_internal.h
 *
 * Headers required by vma.c, which can be substituted accordingly when testing
 * VMA functionality.
 */

#ifndef __MM_VMA_INTERNAL_H
#define __MM_VMA_INTERNAL_H

#include <mikux/backing-dev.h>
#include <mikux/bitops.h>
#include <mikux/bug.h>
#include <mikux/cacheflush.h>
#include <mikux/err.h>
#include <mikux/file.h>
#include <mikux/fs.h>
#include <mikux/huge_mm.h>
#include <mikux/hugetlb_inline.h>
#include <mikux/kernel.h>
#include <mikux/khugepaged.h>
#include <mikux/list.h>
#include <mikux/maple_tree.h>
#include <mikux/mempolicy.h>
#include <mikux/mm.h>
#include <mikux/mm_inline.h>
#include <mikux/mm_types.h>
#include <mikux/mman.h>
#include <mikux/mmap_lock.h>
#include <mikux/mmdebug.h>
#include <mikux/mmu_context.h>
#include <mikux/mutex.h>
#include <mikux/pagemap.h>
#include <mikux/pfn.h>
#include <mikux/rcupdate.h>
#include <mikux/rmap.h>
#include <mikux/rwsem.h>
#include <mikux/sched/signal.h>
#include <mikux/swap.h>
#include <mikux/uprobes.h>
#include <mikux/userfaultfd_k.h>

#include <asm/current.h>
#include <asm/tlb.h>

#include "internal.h"

#endif	/* __MM_VMA_INTERNAL_H */
