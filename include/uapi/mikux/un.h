/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef _MIKUX_UN_H
#define _MIKUX_UN_H

#include <mikux/socket.h>

#define UNIX_PATH_MAX	108

struct sockaddr_un {
	__kernel_sa_family_t sun_family; /* AF_UNIX */
	char sun_path[UNIX_PATH_MAX];	/* pathname */
};

#define SIOCUNIXFILE (SIOCPROTOPRIVATE + 0) /* open a socket file with O_PATH */

#endif /* _MIKUX_UN_H */
