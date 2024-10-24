/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_SECUREBITS_H
#define _MIKUX_SECUREBITS_H 1

#include <uapi/mikux/securebits.h>

#define issecure(X)		(issecure_mask(X) & current_cred_xxx(securebits))
#endif /* !_MIKUX_SECUREBITS_H */
