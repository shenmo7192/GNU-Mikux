/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2012 Netapp, Inc. All rights reserved.
 *
 * Function and structures exported by the NFS module
 * for use by NFS version-specific modules.
 */
#ifndef __MIKUX_INTERNAL_NFS_H
#define __MIKUX_INTERNAL_NFS_H

#include <mikux/fs.h>
#include <mikux/sunrpc/sched.h>
#include <mikux/nfs_xdr.h>

struct nfs_subversion {
	struct module *owner;	/* THIS_MODULE pointer */
	struct file_system_type *nfs_fs;	/* NFS filesystem type */
	const struct rpc_version *rpc_vers;	/* NFS version information */
	const struct nfs_rpc_ops *rpc_ops;	/* NFS operations */
	const struct super_operations *sops;	/* NFS Super operations */
	const struct xattr_handler * const *xattr;	/* NFS xattr handlers */
	struct list_head list;		/* List of NFS versions */
};

struct nfs_subversion *get_nfs_version(unsigned int);
void put_nfs_version(struct nfs_subversion *);
void register_nfs_version(struct nfs_subversion *);
void unregister_nfs_version(struct nfs_subversion *);

#endif /* __MIKUX_INTERNAL_NFS_H */
