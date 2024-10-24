/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_BUG_H
#define _MIKUX_BUG_H

#include <asm/bug.h>

#define BUG_ON(__BUG_ON_cond) assert(!(__BUG_ON_cond))

#define BUG() abort()

#endif /* _MIKUX_BUG_H */
