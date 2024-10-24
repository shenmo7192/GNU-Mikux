/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Atmark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#include <mikux/init.h>
#include <mikux/ftrace.h>
#include <mikux/kernel.h>
#include <mikux/hardirq.h>
#include <mikux/interrupt.h>
#include <mikux/irqflags.h>
#include <mikux/seq_file.h>
#include <mikux/kernel_stat.h>
#include <mikux/irq.h>
#include <mikux/irqchip.h>
#include <mikux/of_irq.h>

void __irq_entry do_IRQ(struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);
	trace_hardirqs_off();

	irq_enter();
	handle_arch_irq(regs);
	irq_exit();
	set_irq_regs(old_regs);
	trace_hardirqs_on();
}

void __init init_IRQ(void)
{
	/* process the entire interrupt tree in one go */
	irqchip_init();
}
