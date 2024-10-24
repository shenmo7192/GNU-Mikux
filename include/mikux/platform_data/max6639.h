/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_MAX6639_H
#define _MIKUX_MAX6639_H

#include <mikux/types.h>

/* platform data for the MAX6639 temperature sensor and fan control */

struct max6639_platform_data {
	bool pwm_polarity;	/* Polarity low (0) or high (1, default) */
	int ppr;		/* Pulses per rotation 1..4 (default == 2) */
	int rpm_range;		/* 2000, 4000 (default), 8000 or 16000 */
};

#endif /* _MIKUX_MAX6639_H */
