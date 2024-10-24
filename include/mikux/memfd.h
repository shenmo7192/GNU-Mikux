/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_MEMFD_H
#define __MIKUX_MEMFD_H

#include <mikux/file.h>

#ifdef CONFIG_MEMFD_CREATE
extern long memfd_fcntl(struct file *file, unsigned int cmd, unsigned int arg);
struct folio *memfd_alloc_folio(struct file *memfd, pgoff_t idx);
#else
static inline long memfd_fcntl(struct file *f, unsigned int c, unsigned int a)
{
	return -EINVAL;
}
static inline struct folio *memfd_alloc_folio(struct file *memfd, pgoff_t idx)
{
	return ERR_PTR(-EINVAL);
}
#endif

#endif /* __MIKUX_MEMFD_H */
