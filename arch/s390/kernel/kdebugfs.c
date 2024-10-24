// SPDX-License-Identifier: GPL-2.0
#include <mikux/debugfs.h>
#include <mikux/export.h>
#include <mikux/init.h>

struct dentry *arch_debugfs_dir;
EXPORT_SYMBOL(arch_debugfs_dir);

static int __init arch_kdebugfs_init(void)
{
	arch_debugfs_dir = debugfs_create_dir("s390", NULL);
	return 0;
}
postcore_initcall(arch_kdebugfs_init);
