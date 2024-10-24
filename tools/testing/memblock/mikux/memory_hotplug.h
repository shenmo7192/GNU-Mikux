/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_MEMORY_HOTPLUG_H
#define _MIKUX_MEMORY_HOTPLUG_H

#include <mikux/numa.h>
#include <mikux/pfn.h>
#include <mikux/cache.h>
#include <mikux/types.h>

extern bool movable_node_enabled;

static inline bool movable_node_is_enabled(void)
{
	return movable_node_enabled;
}

#endif
