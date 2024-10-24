/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  mikux/arch/arm/lib/changebit.S
 *
 *  Copyright (C) 1995-1996 Russell King
 */
#include <mikux/linkage.h>
#include <asm/assembler.h>
#include "bitops.h"
                .text

bitop	_change_bit, eor
