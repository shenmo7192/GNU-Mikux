/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_CRC32C_H
#define _MIKUX_CRC32C_H

#include <mikux/types.h>

extern u32 crc32c(u32 crc, const void *address, unsigned int length);

/* This macro exists for backwards-compatibility. */
#define crc32c_le crc32c

#endif	/* _MIKUX_CRC32C_H */
