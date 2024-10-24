// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Borrowed heavily from MIPS
 */

#include <mikux/export.h>
#include <mikux/extable.h>
#include <mikux/uaccess.h>

int fixup_exception(struct pt_regs *regs)
{
	const struct exception_table_entry *fixup;

	fixup = search_exception_tables(instruction_pointer(regs));
	if (fixup) {
		regs->ret = fixup->fixup;

		return 1;
	}

	return 0;
}
