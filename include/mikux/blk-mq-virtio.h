/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_BLK_MQ_VIRTIO_H
#define _MIKUX_BLK_MQ_VIRTIO_H

struct blk_mq_queue_map;
struct virtio_device;

void blk_mq_virtio_map_queues(struct blk_mq_queue_map *qmap,
		struct virtio_device *vdev, int first_vec);

#endif /* _MIKUX_BLK_MQ_VIRTIO_H */
