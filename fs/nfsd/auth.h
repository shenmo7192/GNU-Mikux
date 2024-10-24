/* SPDX-License-Identifier: GPL-2.0 */
/*
 * nfsd-specific authentication stuff.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#ifndef MIKUX_NFSD_AUTH_H
#define MIKUX_NFSD_AUTH_H

/*
 * Set the current process's fsuid/fsgid etc to those of the NFS
 * client user
 */
int nfsd_setuser(struct svc_cred *cred, struct svc_export *exp);

#endif /* MIKUX_NFSD_AUTH_H */
