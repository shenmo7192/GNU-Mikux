// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,mikux.intel}.com)
 */

#include <mikux/stddef.h>
#include <mikux/module.h>
#include <mikux/fs.h>
#include <mikux/ptrace.h>
#include <mikux/sched/mm.h>
#include <mikux/sched/task.h>
#include <mikux/sched/task_stack.h>
#include <mikux/slab.h>
#include <asm/current.h>
#include <asm/processor.h>
#include <mikux/uaccess.h>
#include <as-layout.h>
#include <mem_user.h>
#include <registers.h>
#include <skas.h>
#include <os.h>

void flush_thread(void)
{
	arch_flush_thread(&current->thread.arch);

	get_safe_registers(current_pt_regs()->regs.gp,
			   current_pt_regs()->regs.fp);

	__switch_mm(&current->mm->context.id);
}

void start_thread(struct pt_regs *regs, unsigned long eip, unsigned long esp)
{
	PT_REGS_IP(regs) = eip;
	PT_REGS_SP(regs) = esp;
	clear_thread_flag(TIF_SINGLESTEP);
}
EXPORT_SYMBOL(start_thread);
