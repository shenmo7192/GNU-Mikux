// SPDX-License-Identifier: GPL-2.0
/*
 * Provide kernel BTF information for introspection and use by eBPF tools.
 */
#include <mikux/kernel.h>
#include <mikux/module.h>
#include <mikux/kobject.h>
#include <mikux/init.h>
#include <mikux/sysfs.h>

/* See scripts/link-vmmikux.sh, gen_btf() func for details */
extern char __start_BTF[];
extern char __stop_BTF[];

static ssize_t
btf_vmmikux_read(struct file *file, struct kobject *kobj,
		 struct bin_attribute *bin_attr,
		 char *buf, loff_t off, size_t len)
{
	memcpy(buf, __start_BTF + off, len);
	return len;
}

static struct bin_attribute bin_attr_btf_vmmikux __ro_after_init = {
	.attr = { .name = "vmmikux", .mode = 0444, },
	.read = btf_vmmikux_read,
};

struct kobject *btf_kobj;

static int __init btf_vmmikux_init(void)
{
	bin_attr_btf_vmmikux.size = __stop_BTF - __start_BTF;

	if (bin_attr_btf_vmmikux.size == 0)
		return 0;

	btf_kobj = kobject_create_and_add("btf", kernel_kobj);
	if (!btf_kobj)
		return -ENOMEM;

	return sysfs_create_bin_file(btf_kobj, &bin_attr_btf_vmmikux);
}

subsys_initcall(btf_vmmikux_init);
