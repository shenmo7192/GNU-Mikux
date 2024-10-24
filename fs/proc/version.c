// SPDX-License-Identifier: GPL-2.0
#include <mikux/fs.h>
#include <mikux/init.h>
#include <mikux/kernel.h>
#include <mikux/proc_fs.h>
#include <mikux/seq_file.h>
#include <mikux/utsname.h>
#include "internal.h"

static int version_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, mikux_proc_banner,
		utsname()->sysname,
		utsname()->release,
		utsname()->version);
	return 0;
}

static int __init proc_version_init(void)
{
	struct proc_dir_entry *pde;

	pde = proc_create_single("version", 0, NULL, version_proc_show);
	pde_make_permanent(pde);
	return 0;
}
fs_initcall(proc_version_init);
