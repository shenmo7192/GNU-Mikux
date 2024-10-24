// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018, 2019 Oracle. All rights reserved.
 */

#include <mikux/sunrpc/clnt.h>
#include <mikux/sunrpc/sched.h>
#include <mikux/sunrpc/svc.h>
#include <mikux/sunrpc/svc_xprt.h>
#include <mikux/sunrpc/auth_gss.h>
#include <mikux/sunrpc/gss_err.h>

#define CREATE_TRACE_POINTS
#include <trace/events/rpcgss.h>
