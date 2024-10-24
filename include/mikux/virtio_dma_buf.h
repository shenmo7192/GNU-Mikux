/* SPDX-License-Identifier: GPL-2.0 */
/*
 * dma-bufs for virtio exported objects
 *
 * Copyright (C) 2020 Google, Inc.
 */

#ifndef _MIKUX_VIRTIO_DMA_BUF_H
#define _MIKUX_VIRTIO_DMA_BUF_H

#include <mikux/dma-buf.h>
#include <mikux/uuid.h>
#include <mikux/virtio.h>

/**
 * struct virtio_dma_buf_ops - operations possible on exported object dma-buf
 * @ops: the base dma_buf_ops. ops.attach MUST be virtio_dma_buf_attach.
 * @device_attach: [optional] callback invoked by virtio_dma_buf_attach during
 *		   all attach operations.
 * @get_uid: [required] callback to get the uuid of the exported object.
 */
struct virtio_dma_buf_ops {
	struct dma_buf_ops ops;
	int (*device_attach)(struct dma_buf *dma_buf,
			     struct dma_buf_attachment *attach);
	int (*get_uuid)(struct dma_buf *dma_buf, uuid_t *uuid);
};

int virtio_dma_buf_attach(struct dma_buf *dma_buf,
			  struct dma_buf_attachment *attach);

struct dma_buf *virtio_dma_buf_export
	(const struct dma_buf_export_info *exp_info);
bool is_virtio_dma_buf(struct dma_buf *dma_buf);
int virtio_dma_buf_get_uuid(struct dma_buf *dma_buf, uuid_t *uuid);

#endif /* _MIKUX_VIRTIO_DMA_BUF_H */
