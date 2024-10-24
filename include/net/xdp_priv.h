/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_NET_XDP_PRIV_H__
#define __MIKUX_NET_XDP_PRIV_H__

#include <mikux/rhashtable.h>
#include <net/xdp.h>

/* Private to net/core/xdp.c, but used by trace/events/xdp.h */
struct xdp_mem_allocator {
	struct xdp_mem_info mem;
	union {
		void *allocator;
		struct page_pool *page_pool;
	};
	struct rhash_head node;
	struct rcu_head rcu;
};

#endif /* __MIKUX_NET_XDP_PRIV_H__ */
