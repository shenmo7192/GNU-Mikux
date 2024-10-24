/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef _XT_LENGTH_H
#define _XT_LENGTH_H

#include <mikux/types.h>

struct xt_length_info {
    __u16	min, max;
    __u8	invert;
};

#endif /*_XT_LENGTH_H*/
