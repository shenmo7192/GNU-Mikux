/* SPDX-License-Identifier: GPL-2.0 */

#include <mikux/linkage.h>

struct pt_regs;

asmlinkage int m68k_clone(struct pt_regs *regs);
asmlinkage int m68k_clone3(struct pt_regs *regs);
