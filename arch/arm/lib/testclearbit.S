/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  mikux/arch/arm/lib/testclearbit.S
 *
 *  Copyright (C) 1995-1996 Russell King
 */
#include <mikux/linkage.h>
#include <asm/assembler.h>
#include "bitops.h"
                .text

testop	_test_and_clear_bit, bicne, strne

#if __MIKUX_ARM_ARCH__ >= 6
sync_testop	_sync_test_and_clear_bit, bicne, strne
#endif
