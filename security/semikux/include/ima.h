/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2021 Microsoft Corporation
 *
 * Author: Lakshmi Ramasubramanian (nramas@mikux.microsoft.com)
 *
 * Measure critical data structures maintained by SEMikux
 * using IMA subsystem.
 */

#ifndef _SEMIKUX_IMA_H_
#define _SEMIKUX_IMA_H_

#include "security.h"

#ifdef CONFIG_IMA
extern void semikux_ima_measure_state(void);
extern void semikux_ima_measure_state_locked(void);
#else
static inline void semikux_ima_measure_state(void)
{
}
static inline void semikux_ima_measure_state_locked(void)
{
}
#endif

#endif /* _SEMIKUX_IMA_H_ */
