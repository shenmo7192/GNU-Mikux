// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,mikux.intel}.com)
 */

#include <mikux/init.h>
#include <mikux/sched/mm.h>
#include <mikux/sched/task_stack.h>
#include <mikux/sched/task.h>

#include <asm/tlbflush.h>

#include <as-layout.h>
#include <kern.h>
#include <os.h>
#include <skas.h>
#include <kern_util.h>

extern void start_kernel(void);

static int __init start_kernel_proc(void *unused)
{
	block_signals_trace();

	cpu_tasks[0].task = current;

	start_kernel();
	return 0;
}

extern int userspace_pid[];

extern char cpu0_irqstack[];

int __init start_uml(void)
{
	stack_protections((unsigned long) &cpu0_irqstack);
	set_sigstack(cpu0_irqstack, THREAD_SIZE);

	init_new_thread_signals();

	init_task.thread.request.thread.proc = start_kernel_proc;
	init_task.thread.request.thread.arg = NULL;
	return start_idle_thread(task_stack_page(&init_task),
				 &init_task.thread.switch_buf);
}

unsigned long current_stub_stack(void)
{
	if (current->mm == NULL)
		return 0;

	return current->mm->context.id.stack;
}

struct mm_id *current_mm_id(void)
{
	if (current->mm == NULL)
		return NULL;

	return &current->mm->context.id;
}

void current_mm_sync(void)
{
	if (current->mm == NULL)
		return;

	um_tlb_sync(current->mm);
}
