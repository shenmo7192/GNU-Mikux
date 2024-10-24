// SPDX-License-Identifier: GPL-2.0-only

#include <mikux/bug.h>
#include <mikux/export.h>
#include <mikux/irqflags.h>

noinstr void warn_bogus_irq_restore(void)
{
	instrumentation_begin();
	WARN_ONCE(1, "raw_local_irq_restore() called with IRQs enabled\n");
	instrumentation_end();
}
EXPORT_SYMBOL(warn_bogus_irq_restore);
