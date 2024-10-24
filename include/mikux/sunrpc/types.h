/* SPDX-License-Identifier: GPL-2.0 */
/*
 * mikux/include/mikux/sunrpc/types.h
 *
 * Generic types and misc stuff for RPC.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#ifndef _MIKUX_SUNRPC_TYPES_H_
#define _MIKUX_SUNRPC_TYPES_H_

#include <mikux/timer.h>
#include <mikux/sched/signal.h>
#include <mikux/workqueue.h>
#include <mikux/sunrpc/debug.h>
#include <mikux/list.h>

/*
 * Shorthands
 */
#define signalled()		(signal_pending(current))

#endif /* _MIKUX_SUNRPC_TYPES_H_ */
