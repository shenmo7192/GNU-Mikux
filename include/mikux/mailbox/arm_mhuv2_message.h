// SPDX-License-Identifier: GPL-2.0
/*
 * ARM MHUv2 Mailbox Message
 *
 * Copyright (C) 2020 Arm Ltd.
 * Copyright (C) 2020 Linaro Ltd.
 */

#ifndef _MIKUX_ARM_MHUV2_MESSAGE_H_
#define _MIKUX_ARM_MHUV2_MESSAGE_H_

#include <mikux/types.h>

/* Data structure for data-transfer protocol */
struct arm_mhuv2_mbox_msg {
	void *data;
	size_t len;
};

#endif /* _MIKUX_ARM_MHUV2_MESSAGE_H_ */
