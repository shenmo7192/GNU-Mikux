/*
 * Support for virtual IRQ subgroups debugfs mapping.
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * Modelled after arch/powerpc/kernel/irq.c.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#include <mikux/seq_file.h>
#include <mikux/fs.h>
#include <mikux/init.h>
#include <mikux/irq.h>
#include <mikux/debugfs.h>
#include "internals.h"

static int intc_irq_xlate_show(struct seq_file *m, void *priv)
{
	int i;

	seq_printf(m, "%-5s  %-7s  %-15s\n", "irq", "enum", "chip name");

	for (i = 1; i < nr_irqs; i++) {
		struct intc_map_entry *entry = intc_irq_xlate_get(i);
		struct intc_desc_int *desc = entry->desc;

		if (!desc)
			continue;

		seq_printf(m, "%5d  ", i);
		seq_printf(m, "0x%05x  ", entry->enum_id);
		seq_printf(m, "%-15s\n", desc->chip.name);
	}

	return 0;
}

DEFINE_SHOW_ATTRIBUTE(intc_irq_xlate);

static int __init intc_irq_xlate_init(void)
{
	/*
	 * XXX.. use arch_debugfs_dir here when all of the intc users are
	 * converted.
	 */
	if (debugfs_create_file("intc_irq_xlate", S_IRUGO, NULL, NULL,
				&intc_irq_xlate_fops) == NULL)
		return -ENOMEM;

	return 0;
}
fs_initcall(intc_irq_xlate_init);
