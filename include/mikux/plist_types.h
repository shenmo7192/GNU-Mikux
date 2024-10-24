/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef _MIKUX_PLIST_TYPES_H
#define _MIKUX_PLIST_TYPES_H

#include <mikux/types.h>

struct plist_head {
	struct list_head node_list;
};

struct plist_node {
	int			prio;
	struct list_head	prio_list;
	struct list_head	node_list;
};

#endif /* _MIKUX_PLIST_TYPES_H */
