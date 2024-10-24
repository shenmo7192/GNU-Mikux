/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  mikux/arch/arm/lib/testsetbit.S
 *
 *  Copyright (C) 1995-1996 Russell King
 */
#include <mikux/linkage.h>
#include <asm/assembler.h>
#include "bitops.h"
                .text

testop	_test_and_set_bit, orreq, streq

#if __MIKUX_ARM_ARCH__ >= 6
sync_testop	_sync_test_and_set_bit, orreq, streq
#endif
