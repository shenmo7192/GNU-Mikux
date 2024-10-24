// SPDX-License-Identifier: GPL-2.0

#include <mikux/blk-mq.h>
#include <mikux/blkdev.h>

void *rust_helper_blk_mq_rq_to_pdu(struct request *rq)
{
	return blk_mq_rq_to_pdu(rq);
}

struct request *rust_helper_blk_mq_rq_from_pdu(void *pdu)
{
	return blk_mq_rq_from_pdu(pdu);
}
