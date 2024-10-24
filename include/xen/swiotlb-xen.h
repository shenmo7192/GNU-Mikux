/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_SWIOTLB_XEN_H
#define __MIKUX_SWIOTLB_XEN_H

#include <mikux/swiotlb.h>
#include <asm/xen/swiotlb-xen.h>

void xen_dma_sync_for_cpu(struct device *dev, dma_addr_t handle,
			  size_t size, enum dma_data_direction dir);
void xen_dma_sync_for_device(struct device *dev, dma_addr_t handle,
			     size_t size, enum dma_data_direction dir);

extern const struct dma_map_ops xen_swiotlb_dma_ops;

#endif /* __MIKUX_SWIOTLB_XEN_H */
