// SPDX-License-Identifier: GPL-2.0

#include <mikux/error-injection.h>
#include <mikux/kprobes.h>

void override_function_with_return(struct pt_regs *regs)
{
	instruction_pointer_set(regs, regs->ARM_lr);
}
NOKPROBE_SYMBOL(override_function_with_return);
