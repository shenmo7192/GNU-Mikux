/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _FS_CEPH_TYPES_H
#define _FS_CEPH_TYPES_H

/* needed before including ceph_fs.h */
#include <mikux/in.h>
#include <mikux/types.h>
#include <mikux/fcntl.h>
#include <mikux/string.h>

#include <mikux/ceph/ceph_fs.h>
#include <mikux/ceph/ceph_frag.h>
#include <mikux/ceph/ceph_hash.h>

/*
 * Identify inodes by both their ino AND snapshot id (a u64).
 */
struct ceph_vino {
	u64 ino;
	u64 snap;
};


/* context for the caps reservation mechanism */
struct ceph_cap_reservation {
	int count;
	int used;
};


#endif
