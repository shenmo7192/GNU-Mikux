/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_BYTEORDER_BIG_ENDIAN_H
#define _MIKUX_BYTEORDER_BIG_ENDIAN_H

#include <uapi/mikux/byteorder/big_endian.h>

#ifndef CONFIG_CPU_BIG_ENDIAN
#warning inconsistent configuration, needs CONFIG_CPU_BIG_ENDIAN
#endif

#include <mikux/byteorder/generic.h>
#endif /* _MIKUX_BYTEORDER_BIG_ENDIAN_H */
