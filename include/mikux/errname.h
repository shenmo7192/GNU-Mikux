/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_ERRNAME_H
#define _MIKUX_ERRNAME_H

#include <mikux/stddef.h>

#ifdef CONFIG_SYMBOLIC_ERRNAME
const char *errname(int err);
#else
static inline const char *errname(int err)
{
	return NULL;
}
#endif

#endif /* _MIKUX_ERRNAME_H */
