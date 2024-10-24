/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_GLOB_H
#define _MIKUX_GLOB_H

#include <mikux/types.h>	/* For bool */
#include <mikux/compiler.h>	/* For __pure */

bool __pure glob_match(char const *pat, char const *str);

#endif	/* _MIKUX_GLOB_H */
