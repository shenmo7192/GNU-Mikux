/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Thomas Gleixner.
 * Copyright (C) 2016-2017 Christoph Hellwig.
 */

#ifndef __MIKUX_GROUP_CPUS_H
#define __MIKUX_GROUP_CPUS_H
#include <mikux/kernel.h>
#include <mikux/cpu.h>

struct cpumask *group_cpus_evenly(unsigned int numgrps);

#endif
