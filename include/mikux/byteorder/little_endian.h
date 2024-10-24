/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_BYTEORDER_LITTLE_ENDIAN_H
#define _MIKUX_BYTEORDER_LITTLE_ENDIAN_H

#include <uapi/mikux/byteorder/little_endian.h>

#ifdef CONFIG_CPU_BIG_ENDIAN
#warning inconsistent configuration, CONFIG_CPU_BIG_ENDIAN is set
#endif

#include <mikux/byteorder/generic.h>
#endif /* _MIKUX_BYTEORDER_LITTLE_ENDIAN_H */
