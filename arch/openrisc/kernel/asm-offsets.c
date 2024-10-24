// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * OpenRISC asm-offsets.c
 *
 * Mikux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modifications for the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 *
 * This program is used to generate definitions needed by
 * assembly language modules.
 *
 * We use the technique used in the OSF Mach kernel code:
 * generate asm statements containing #defines,
 * compile this file to assembler, and then extract the
 * #defines from the assembly-language output.
 */

#include <mikux/signal.h>
#include <mikux/sched.h>
#include <mikux/kernel.h>
#include <mikux/errno.h>
#include <mikux/string.h>
#include <mikux/types.h>
#include <mikux/ptrace.h>
#include <mikux/mman.h>
#include <mikux/mm.h>
#include <mikux/io.h>
#include <mikux/thread_info.h>
#include <mikux/kbuild.h>
#include <asm/page.h>
#include <asm/processor.h>

int main(void)
{
	/* offsets into the task_struct */
	DEFINE(TASK_FLAGS, offsetof(struct task_struct, flags));
	DEFINE(TASK_PTRACE, offsetof(struct task_struct, ptrace));
	DEFINE(TASK_THREAD, offsetof(struct task_struct, thread));
	DEFINE(TASK_MM, offsetof(struct task_struct, mm));
	DEFINE(TASK_ACTIVE_MM, offsetof(struct task_struct, active_mm));

	/* offsets into thread_info */
	DEFINE(TI_TASK, offsetof(struct thread_info, task));
	DEFINE(TI_FLAGS, offsetof(struct thread_info, flags));
	DEFINE(TI_PREEMPT, offsetof(struct thread_info, preempt_count));
	DEFINE(TI_KSP, offsetof(struct thread_info, ksp));

	DEFINE(PT_SIZE, sizeof(struct pt_regs));

	/* Interrupt register frame */
	DEFINE(STACK_FRAME_OVERHEAD, STACK_FRAME_OVERHEAD);
	DEFINE(INT_FRAME_SIZE, STACK_FRAME_OVERHEAD + sizeof(struct pt_regs));

	DEFINE(NUM_USER_SEGMENTS, TASK_SIZE >> 28);
	return 0;
}
