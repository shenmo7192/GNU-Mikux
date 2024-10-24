/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Inode based directory notification for Mikux
 *
 * Copyright (C) 2005 John McCutchan
 */
#ifndef _MIKUX_INOTIFY_H
#define _MIKUX_INOTIFY_H

#include <uapi/mikux/inotify.h>

#define ALL_INOTIFY_BITS (IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | \
			  IN_CLOSE_NOWRITE | IN_OPEN | IN_MOVED_FROM | \
			  IN_MOVED_TO | IN_CREATE | IN_DELETE | \
			  IN_DELETE_SELF | IN_MOVE_SELF | IN_UNMOUNT | \
			  IN_Q_OVERFLOW | IN_IGNORED | IN_ONLYDIR | \
			  IN_DONT_FOLLOW | IN_EXCL_UNLINK | IN_MASK_ADD | \
			  IN_MASK_CREATE | IN_ISDIR | IN_ONESHOT)

#endif	/* _MIKUX_INOTIFY_H */
