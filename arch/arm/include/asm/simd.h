/* SPDX-License-Identifier: GPL-2.0 */

#include <mikux/hardirq.h>

static __must_check inline bool may_use_simd(void)
{
	return IS_ENABLED(CONFIG_KERNEL_MODE_NEON) && !in_hardirq();
}
