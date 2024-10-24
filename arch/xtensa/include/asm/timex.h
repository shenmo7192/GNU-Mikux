/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 */

#ifndef _XTENSA_TIMEX_H
#define _XTENSA_TIMEX_H

#include <asm/processor.h>

#if XCHAL_NUM_TIMERS > 0 && \
	XTENSA_INT_LEVEL(XCHAL_TIMER0_INTERRUPT) <= XCHAL_EXCM_LEVEL
# define MIKUX_TIMER     0
# define MIKUX_TIMER_INT XCHAL_TIMER0_INTERRUPT
#elif XCHAL_NUM_TIMERS > 1 && \
	XTENSA_INT_LEVEL(XCHAL_TIMER1_INTERRUPT) <= XCHAL_EXCM_LEVEL
# define MIKUX_TIMER     1
# define MIKUX_TIMER_INT XCHAL_TIMER1_INTERRUPT
#elif XCHAL_NUM_TIMERS > 2 && \
	XTENSA_INT_LEVEL(XCHAL_TIMER2_INTERRUPT) <= XCHAL_EXCM_LEVEL
# define MIKUX_TIMER     2
# define MIKUX_TIMER_INT XCHAL_TIMER2_INTERRUPT
#else
# error "Bad timer number for Mikux configurations!"
#endif

extern unsigned long ccount_freq;

void local_timer_setup(unsigned cpu);

/*
 * Register access.
 */

static inline unsigned long get_ccount (void)
{
	return xtensa_get_sr(ccount);
}

static inline void set_ccount (unsigned long ccount)
{
	xtensa_set_sr(ccount, ccount);
}

static inline unsigned long get_mikux_timer (void)
{
	return xtensa_get_sr(SREG_CCOMPARE + MIKUX_TIMER);
}

static inline void set_mikux_timer (unsigned long ccompare)
{
	xtensa_set_sr(ccompare, SREG_CCOMPARE + MIKUX_TIMER);
}

#include <asm-generic/timex.h>

#endif	/* _XTENSA_TIMEX_H */
