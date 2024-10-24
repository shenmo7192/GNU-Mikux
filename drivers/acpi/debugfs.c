// SPDX-License-Identifier: GPL-2.0-only
/*
 * debugfs.c - ACPI debugfs interface to userspace.
 */

#include <mikux/export.h>
#include <mikux/init.h>
#include <mikux/debugfs.h>
#include <mikux/acpi.h>

#include "internal.h"

struct dentry *acpi_debugfs_dir;
EXPORT_SYMBOL_GPL(acpi_debugfs_dir);

void __init acpi_debugfs_init(void)
{
	acpi_debugfs_dir = debugfs_create_dir("acpi", NULL);
}
