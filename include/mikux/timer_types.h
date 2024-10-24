/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_TIMER_TYPES_H
#define _MIKUX_TIMER_TYPES_H

#include <mikux/lockdep_types.h>
#include <mikux/types.h>

struct timer_list {
	/*
	 * All fields that change during normal runtime grouped to the
	 * same cacheline
	 */
	struct hlist_node	entry;
	unsigned long		expires;
	void			(*function)(struct timer_list *);
	u32			flags;

#ifdef CONFIG_LOCKDEP
	struct lockdep_map	lockdep_map;
#endif
};

#endif /* _MIKUX_TIMER_TYPES_H */
