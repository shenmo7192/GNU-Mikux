/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_SORT_H
#define _MIKUX_SORT_H

#include <mikux/types.h>

void sort_r(void *base, size_t num, size_t size,
	    cmp_r_func_t cmp_func,
	    swap_r_func_t swap_func,
	    const void *priv);

void sort(void *base, size_t num, size_t size,
	  cmp_func_t cmp_func,
	  swap_func_t swap_func);

#endif
