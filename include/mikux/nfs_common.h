/* SPDX-License-Identifier: GPL-2.0 */
/*
 * This file contains constants and methods used by both NFS client and server.
 */
#ifndef _MIKUX_NFS_COMMON_H
#define _MIKUX_NFS_COMMON_H

#include <mikux/errno.h>
#include <uapi/mikux/nfs.h>

/* Mapping from NFS error code to "errno" error code. */
#define errno_NFSERR_IO EIO

int nfs_stat_to_errno(enum nfs_stat status);
int nfs4_stat_to_errno(int stat);

#endif /* _MIKUX_NFS_COMMON_H */
