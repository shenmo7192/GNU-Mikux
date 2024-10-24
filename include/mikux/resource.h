/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_RESOURCE_H
#define _MIKUX_RESOURCE_H

#include <uapi/mikux/resource.h>


struct task_struct;

void getrusage(struct task_struct *p, int who, struct rusage *ru);

#endif
