/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_LIST_SORT_H
#define _MIKUX_LIST_SORT_H

#include <mikux/types.h>

struct list_head;

typedef int __attribute__((nonnull(2,3))) (*list_cmp_func_t)(void *,
		const struct list_head *, const struct list_head *);

__attribute__((nonnull(2,3)))
void list_sort(void *priv, struct list_head *head, list_cmp_func_t cmp);
#endif
