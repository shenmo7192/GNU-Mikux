/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#ifndef _MIKUX_CORESIGHT_PMU_H
#define _MIKUX_CORESIGHT_PMU_H

#include <mikux/bits.h>

#define CORESIGHT_ETM_PMU_NAME "cs_etm"

/*
 * The legacy Trace ID system based on fixed calculation from the cpu
 * number. This has been replaced by drivers using a dynamic allocation
 * system - but need to retain the legacy algorithm for backward comparibility
 * in certain situations:-
 * a) new perf running on older systems that generate the legacy mapping
 * b) older tools that may not update at the same time as the kernel.
 */
#define CORESIGHT_LEGACY_CPU_TRACE_ID(cpu)  (0x10 + (cpu * 2))

/*
 * Below are the definition of bit offsets for perf option, and works as
 * arbitrary values for all ETM versions.
 *
 * Most of them are orignally from ETMv3.5/PTM's ETMCR config, therefore,
 * ETMv3.5/PTM doesn't define ETMCR config bits with prefix "ETM3_" and
 * directly use below macros as config bits.
 */
#define ETM_OPT_BRANCH_BROADCAST 8
#define ETM_OPT_CYCACC		12
#define ETM_OPT_CTXTID		14
#define ETM_OPT_CTXTID2		15
#define ETM_OPT_TS		28
#define ETM_OPT_RETSTK		29

/* ETMv4 CONFIGR programming bits for the ETM OPTs */
#define ETM4_CFG_BIT_BB         3
#define ETM4_CFG_BIT_CYCACC	4
#define ETM4_CFG_BIT_CTXTID	6
#define ETM4_CFG_BIT_VMID	7
#define ETM4_CFG_BIT_TS		11
#define ETM4_CFG_BIT_RETSTK	12
#define ETM4_CFG_BIT_VMID_OPT	15

/*
 * Interpretation of the PERF_RECORD_AUX_OUTPUT_HW_ID payload.
 * Used to associate a CPU with the CoreSight Trace ID.
 * [07:00] - Trace ID - uses 8 bits to make value easy to read in file.
 * [39:08] - Sink ID - as reported in /sys/bus/event_source/devices/cs_etm/sinks/
 *	      Added in minor version 1.
 * [55:40] - Unused (SBZ)
 * [59:56] - Minor Version - previously existing fields are compatible with
 *	      all minor versions.
 * [63:60] - Major Version - previously existing fields mean different things
 *	      in new major versions.
 */
#define CS_AUX_HW_ID_TRACE_ID_MASK	GENMASK_ULL(7, 0)
#define CS_AUX_HW_ID_SINK_ID_MASK	GENMASK_ULL(39, 8)

#define CS_AUX_HW_ID_MINOR_VERSION_MASK	GENMASK_ULL(59, 56)
#define CS_AUX_HW_ID_MAJOR_VERSION_MASK	GENMASK_ULL(63, 60)

#define CS_AUX_HW_ID_MAJOR_VERSION 0
#define CS_AUX_HW_ID_MINOR_VERSION 1

#endif
