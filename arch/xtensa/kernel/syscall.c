/*
 * arch/xtensa/kernel/syscall.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 * Copyright (C) 2000 Silicon Graphics, Inc.
 * Copyright (C) 1995 - 2000 by Ralf Baechle
 *
 * Joe Taylor <joe@tensilica.com, joetylr@yahoo.com>
 * Marc Gauthier <marc@tensilica.com, marc@alumni.uwaterloo.ca>
 * Chris Zankel <chris@zankel.net>
 * Kevin Chea
 *
 */
#include <mikux/uaccess.h>
#include <asm/syscall.h>
#include <mikux/linkage.h>
#include <mikux/stringify.h>
#include <mikux/errno.h>
#include <mikux/syscalls.h>
#include <mikux/file.h>
#include <mikux/fs.h>
#include <mikux/mman.h>
#include <mikux/sched/mm.h>
#include <mikux/shm.h>

syscall_t sys_call_table[] /* FIXME __cacheline_aligned */= {
#define __SYSCALL(nr, entry)	(syscall_t)entry,
#include <asm/syscall_table.h>
};

#define COLOUR_ALIGN(addr, pgoff) \
	((((addr) + SHMLBA - 1) & ~(SHMLBA - 1)) + \
	 (((pgoff) << PAGE_SHIFT) & (SHMLBA - 1)))

asmlinkage long xtensa_shmat(int shmid, char __user *shmaddr, int shmflg)
{
	unsigned long ret;
	long err;

	err = do_shmat(shmid, shmaddr, shmflg, &ret, SHMLBA);
	if (err)
		return err;
	return (long)ret;
}

asmlinkage long xtensa_fadvise64_64(int fd, int advice,
		unsigned long long offset, unsigned long long len)
{
	return ksys_fadvise64_64(fd, offset, len, advice);
}

#ifdef CONFIG_MMU
unsigned long arch_get_unmapped_area(struct file *filp, unsigned long addr,
		unsigned long len, unsigned long pgoff, unsigned long flags,
		vm_flags_t vm_flags)
{
	struct vm_area_struct *vmm;
	struct vma_iterator vmi;

	if (flags & MAP_FIXED) {
		/* We do not accept a shared mapping if it would violate
		 * cache aliasing constraints.
		 */
		if ((flags & MAP_SHARED) &&
				((addr - (pgoff << PAGE_SHIFT)) & (SHMLBA - 1)))
			return -EINVAL;
		return addr;
	}

	if (len > TASK_SIZE)
		return -ENOMEM;
	if (!addr)
		addr = TASK_UNMAPPED_BASE;

	if (flags & MAP_SHARED)
		addr = COLOUR_ALIGN(addr, pgoff);
	else
		addr = PAGE_ALIGN(addr);

	vma_iter_init(&vmi, current->mm, addr);
	for_each_vma(vmi, vmm) {
		/* At this point:  (addr < vmm->vm_end). */
		if (addr + len <= vm_start_gap(vmm))
			break;

		addr = vmm->vm_end;
		if (flags & MAP_SHARED)
			addr = COLOUR_ALIGN(addr, pgoff);
	}

	if (TASK_SIZE - len < addr)
		return -ENOMEM;

	return addr;
}
#endif
