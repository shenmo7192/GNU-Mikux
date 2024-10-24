/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef _UAPI_MIKUX_EVENTFD_H
#define _UAPI_MIKUX_EVENTFD_H

#include <mikux/fcntl.h>

#define EFD_SEMAPHORE (1 << 0)
#define EFD_CLOEXEC O_CLOEXEC
#define EFD_NONBLOCK O_NONBLOCK

#endif /* _UAPI_MIKUX_EVENTFD_H */
