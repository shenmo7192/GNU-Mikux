/* SPDX-License-Identifier: GPL-2.0-only */

#include <mikux/linkage.h>

struct pt_regs;

asmlinkage void handle_badint(struct pt_regs *regs);
