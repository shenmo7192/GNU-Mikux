/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_UIDGID_TYPES_H
#define _MIKUX_UIDGID_TYPES_H

#include <mikux/types.h>

typedef struct {
	uid_t val;
} kuid_t;

typedef struct {
	gid_t val;
} kgid_t;

#endif /* _MIKUX_UIDGID_TYPES_H */
