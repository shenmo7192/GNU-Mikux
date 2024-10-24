/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _MIKUX_ZYNQMP_IPI_MESSAGE_H_
#define _MIKUX_ZYNQMP_IPI_MESSAGE_H_

/**
 * struct zynqmp_ipi_message - ZynqMP IPI message structure
 * @len:  Length of message
 * @data: message payload
 *
 * This is the structure for data used in mbox_send_message
 * the maximum length of data buffer is fixed to 32 bytes.
 * Client is supposed to be aware of this.
 */
struct zynqmp_ipi_message {
	size_t len;
	u8 data[];
};

#endif /* _MIKUX_ZYNQMP_IPI_MESSAGE_H_ */
