/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
/*
 * mikux/include/mikux/nfsd/stats.h
 *
 * Statistics for NFS server.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#ifndef _UAPIMIKUX_NFSD_STATS_H
#define _UAPIMIKUX_NFSD_STATS_H

#include <mikux/nfs4.h>

/* thread usage wraps very million seconds (approx one fortnight) */
#define	NFSD_USAGE_WRAP	(HZ*1000000)

#endif /* _UAPIMIKUX_NFSD_STATS_H */
