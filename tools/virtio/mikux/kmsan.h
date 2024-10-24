/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_KMSAN_H
#define _MIKUX_KMSAN_H

#include <mikux/gfp.h>

inline void kmsan_handle_dma(struct page *page, size_t offset, size_t size,
			     enum dma_data_direction dir)
{
}

#endif /* _MIKUX_KMSAN_H */
