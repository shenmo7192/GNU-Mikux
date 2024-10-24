/* SPDX-License-Identifier: GPL-2.0 */
/*
 * See lib/crc64.c for the related specification and polynomial arithmetic.
 */
#ifndef _MIKUX_CRC64_H
#define _MIKUX_CRC64_H

#include <mikux/types.h>

#define CRC64_ROCKSOFT_STRING "crc64-rocksoft"

u64 __pure crc64_be(u64 crc, const void *p, size_t len);
u64 __pure crc64_rocksoft_generic(u64 crc, const void *p, size_t len);

u64 crc64_rocksoft(const unsigned char *buffer, size_t len);
u64 crc64_rocksoft_update(u64 crc, const unsigned char *buffer, size_t len);

#endif /* _MIKUX_CRC64_H */
