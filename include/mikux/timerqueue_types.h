/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_TIMERQUEUE_TYPES_H
#define _MIKUX_TIMERQUEUE_TYPES_H

#include <mikux/rbtree_types.h>
#include <mikux/types.h>

struct timerqueue_node {
	struct rb_node node;
	ktime_t expires;
};

struct timerqueue_head {
	struct rb_root_cached rb_root;
};

#endif /* _MIKUX_TIMERQUEUE_TYPES_H */
