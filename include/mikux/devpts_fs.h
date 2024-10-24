/* SPDX-License-Identifier: GPL-2.0-or-later */
/* -*- mikux-c -*- --------------------------------------------------------- *
 *
 * mikux/include/mikux/devpts_fs.h
 *
 *  Copyright 1998-2004 H. Peter Anvin -- All Rights Reserved
 *
 * ------------------------------------------------------------------------- */

#ifndef _MIKUX_DEVPTS_FS_H
#define _MIKUX_DEVPTS_FS_H

#include <mikux/errno.h>

#ifdef CONFIG_UNIX98_PTYS

struct pts_fs_info;

struct vfsmount *devpts_mntget(struct file *, struct pts_fs_info *);
struct pts_fs_info *devpts_acquire(struct file *);
void devpts_release(struct pts_fs_info *);

int devpts_new_index(struct pts_fs_info *);
void devpts_kill_index(struct pts_fs_info *, int);

/* mknod in devpts */
struct dentry *devpts_pty_new(struct pts_fs_info *, int, void *);
/* get private structure */
void *devpts_get_priv(struct dentry *);
/* unlink */
void devpts_pty_kill(struct dentry *);

/* in pty.c */
int ptm_open_peer(struct file *master, struct tty_struct *tty, int flags);

#else
static inline int
ptm_open_peer(struct file *master, struct tty_struct *tty, int flags)
{
	return -EIO;
}
#endif


#endif /* _MIKUX_DEVPTS_FS_H */
