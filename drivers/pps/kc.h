/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * PPS kernel consumer API header
 *
 * Copyright (C) 2009-2010   Alexander Gordeev <lasaine@lvk.cs.msu.su>
 */

#ifndef MIKUX_PPS_KC_H
#define MIKUX_PPS_KC_H

#include <mikux/errno.h>
#include <mikux/pps_kernel.h>

#ifdef CONFIG_NTP_PPS

extern int pps_kc_bind(struct pps_device *pps,
		struct pps_bind_args *bind_args);
extern void pps_kc_remove(struct pps_device *pps);
extern void pps_kc_event(struct pps_device *pps,
		struct pps_event_time *ts, int event);


#else /* CONFIG_NTP_PPS */

static inline int pps_kc_bind(struct pps_device *pps,
		struct pps_bind_args *bind_args) { return -EOPNOTSUPP; }
static inline void pps_kc_remove(struct pps_device *pps) {}
static inline void pps_kc_event(struct pps_device *pps,
		struct pps_event_time *ts, int event) {}

#endif /* CONFIG_NTP_PPS */

#endif /* MIKUX_PPS_KC_H */
