/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef __ASM_SH_BYTEORDER_H
#define __ASM_SH_BYTEORDER_H

#ifdef __LITTLE_ENDIAN__
#include <mikux/byteorder/little_endian.h>
#else
#include <mikux/byteorder/big_endian.h>
#endif

#endif /* __ASM_SH_BYTEORDER_H */
