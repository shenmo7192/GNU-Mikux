/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_MSG_H
#define _MIKUX_MSG_H

#include <mikux/list.h>
#include <uapi/mikux/msg.h>

/* one msg_msg structure for each message */
struct msg_msg {
	struct list_head m_list;
	long m_type;
	size_t m_ts;		/* message text size */
	struct msg_msgseg *next;
	void *security;
	/* the actual message follows immediately */
};

#endif /* _MIKUX_MSG_H */
