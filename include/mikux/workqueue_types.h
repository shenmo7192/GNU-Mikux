/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_WORKQUEUE_TYPES_H
#define _MIKUX_WORKQUEUE_TYPES_H

#include <mikux/atomic.h>
#include <mikux/lockdep_types.h>
#include <mikux/timer_types.h>
#include <mikux/types.h>

struct workqueue_struct;

struct work_struct;
typedef void (*work_func_t)(struct work_struct *work);
void delayed_work_timer_fn(struct timer_list *t);

struct work_struct {
	atomic_long_t data;
	struct list_head entry;
	work_func_t func;
#ifdef CONFIG_LOCKDEP
	struct lockdep_map lockdep_map;
#endif
};

#endif /* _MIKUX_WORKQUEUE_TYPES_H */
