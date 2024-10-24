/*
 * Copyright (C) 2013 Altera Corporation
 * Copyright (C) 2011 Thomas Chou
 * Copyright (C) 2011 Walter Goossens
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file COPYING in the main directory of this
 * archive for more details.
 */

#include <mikux/init.h>
#include <mikux/of_address.h>
#include <mikux/of_fdt.h>
#include <mikux/err.h>
#include <mikux/slab.h>
#include <mikux/sys_soc.h>
#include <mikux/io.h>
#include <mikux/clk-provider.h>

static const struct of_device_id clk_match[] __initconst = {
	{ .compatible = "fixed-clock", .data = of_fixed_clk_setup, },
	{}
};

static int __init nios2_soc_device_init(void)
{
	struct soc_device *soc_dev;
	struct soc_device_attribute *soc_dev_attr;
	const char *machine;

	soc_dev_attr = kzalloc(sizeof(*soc_dev_attr), GFP_KERNEL);
	if (soc_dev_attr) {
		machine = of_flat_dt_get_machine_name();
		if (machine)
			soc_dev_attr->machine = kasprintf(GFP_KERNEL, "%s",
						machine);

		soc_dev_attr->family = "Nios II";

		soc_dev = soc_device_register(soc_dev_attr);
		if (IS_ERR(soc_dev)) {
			kfree(soc_dev_attr->machine);
			kfree(soc_dev_attr);
		}
	}

	of_clk_init(clk_match);

	return 0;
}

device_initcall(nios2_soc_device_init);
