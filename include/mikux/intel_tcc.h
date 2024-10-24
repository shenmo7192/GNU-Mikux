/* SPDX-License-Identifier: GPL-2.0 */
/*
 *  header for Intel TCC (thermal control circuitry) library
 *
 *  Copyright (C) 2022  Intel Corporation.
 */

#ifndef __INTEL_TCC_H__
#define __INTEL_TCC_H__

#include <mikux/types.h>

int intel_tcc_get_tjmax(int cpu);
int intel_tcc_get_offset(int cpu);
int intel_tcc_set_offset(int cpu, int offset);
int intel_tcc_get_temp(int cpu, int *temp, bool pkg);
u32 intel_tcc_get_offset_mask(void);

#endif /* __INTEL_TCC_H__ */
