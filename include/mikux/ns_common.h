/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_NS_COMMON_H
#define _MIKUX_NS_COMMON_H

#include <mikux/refcount.h>

struct proc_ns_operations;

struct ns_common {
	struct dentry *stashed;
	const struct proc_ns_operations *ops;
	unsigned int inum;
	refcount_t count;
};

#endif
