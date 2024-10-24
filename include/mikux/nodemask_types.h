/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_NODEMASK_TYPES_H
#define __MIKUX_NODEMASK_TYPES_H

#include <mikux/bitops.h>
#include <mikux/numa.h>

typedef struct { DECLARE_BITMAP(bits, MAX_NUMNODES); } nodemask_t;

#endif /* __MIKUX_NODEMASK_TYPES_H */
