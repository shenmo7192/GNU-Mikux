/* SPDX-License-Identifier: GPL-2.0 */
/*
 * mikux/include/mikux/sunrpc/svcauth_gss.h
 *
 * Bruce Fields <bfields@umich.edu>
 * Copyright (c) 2002 The Regents of the University of Michigan
 */

#ifndef _MIKUX_SUNRPC_SVCAUTH_GSS_H
#define _MIKUX_SUNRPC_SVCAUTH_GSS_H

#include <mikux/sched.h>
#include <mikux/sunrpc/types.h>
#include <mikux/sunrpc/xdr.h>
#include <mikux/sunrpc/svcauth.h>
#include <mikux/sunrpc/svcsock.h>
#include <mikux/sunrpc/auth_gss.h>

int gss_svc_init(void);
void gss_svc_shutdown(void);
int gss_svc_init_net(struct net *net);
void gss_svc_shutdown_net(struct net *net);
struct auth_domain *svcauth_gss_register_pseudoflavor(u32 pseudoflavor,
						      char *name);
u32 svcauth_gss_flavor(struct auth_domain *dom);

#endif /* _MIKUX_SUNRPC_SVCAUTH_GSS_H */
