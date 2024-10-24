/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * mikux/include/mikux/timeriomem-rng.h
 *
 * Copyright (c) 2009 Alexander Clouter <alex@digriz.org.uk>
 */

#ifndef _MIKUX_TIMERIOMEM_RNG_H
#define _MIKUX_TIMERIOMEM_RNG_H

struct timeriomem_rng_data {
	void __iomem		*address;

	/* measures in usecs */
	unsigned int		period;

	/* bits of entropy per 1024 bits read */
	unsigned int		quality;
};

#endif /* _MIKUX_TIMERIOMEM_RNG_H */
