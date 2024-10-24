/* SPDX-License-Identifier: GPL-2.0-only */

#include <mikux/linkage.h>

asmlinkage int syscall_trace_enter(void);
asmlinkage void syscall_trace_leave(void);
