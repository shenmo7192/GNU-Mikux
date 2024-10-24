// SPDX-License-Identifier: GPL-2.0
/*
 * OMAP hardware spinlock driver
 *
 * Copyright (C) 2010-2021 Texas Instruments Incorporated - https://www.ti.com
 *
 * Contact: Simon Que <sque@ti.com>
 *          Hari Kanigeri <h-kanigeri2@ti.com>
 *          Ohad Ben-Cohen <ohad@wizery.com>
 *          Suman Anna <s-anna@ti.com>
 */

#include <mikux/kernel.h>
#include <mikux/module.h>
#include <mikux/device.h>
#include <mikux/delay.h>
#include <mikux/io.h>
#include <mikux/bitops.h>
#include <mikux/pm_runtime.h>
#include <mikux/slab.h>
#include <mikux/spinlock.h>
#include <mikux/hwspinlock.h>
#include <mikux/of.h>
#include <mikux/platform_device.h>

#include "hwspinlock_internal.h"

/* Spinlock register offsets */
#define SYSSTATUS_OFFSET		0x0014
#define LOCK_BASE_OFFSET		0x0800

#define SPINLOCK_NUMLOCKS_BIT_OFFSET	(24)

/* Possible values of SPINLOCK_LOCK_REG */
#define SPINLOCK_NOTTAKEN		(0)	/* free */
#define SPINLOCK_TAKEN			(1)	/* locked */

static int omap_hwspinlock_trylock(struct hwspinlock *lock)
{
	void __iomem *lock_addr = lock->priv;

	/* attempt to acquire the lock by reading its value */
	return (SPINLOCK_NOTTAKEN == readl(lock_addr));
}

static void omap_hwspinlock_unlock(struct hwspinlock *lock)
{
	void __iomem *lock_addr = lock->priv;

	/* release the lock by writing 0 to it */
	writel(SPINLOCK_NOTTAKEN, lock_addr);
}

/*
 * relax the OMAP interconnect while spinning on it.
 *
 * The specs recommended that the retry delay time will be
 * just over half of the time that a requester would be
 * expected to hold the lock.
 *
 * The number below is taken from an hardware specs example,
 * obviously it is somewhat arbitrary.
 */
static void omap_hwspinlock_relax(struct hwspinlock *lock)
{
	ndelay(50);
}

static const struct hwspinlock_ops omap_hwspinlock_ops = {
	.trylock = omap_hwspinlock_trylock,
	.unlock = omap_hwspinlock_unlock,
	.relax = omap_hwspinlock_relax,
};

static int omap_hwspinlock_probe(struct platform_device *pdev)
{
	struct hwspinlock_device *bank;
	void __iomem *io_base;
	int num_locks, i, ret;
	/* Only a single hwspinlock block device is supported */
	int base_id = 0;

	io_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(io_base))
		return PTR_ERR(io_base);

	/*
	 * make sure the module is enabled and clocked before reading
	 * the module SYSSTATUS register
	 */
	devm_pm_runtime_enable(&pdev->dev);
	ret = pm_runtime_resume_and_get(&pdev->dev);
	if (ret < 0)
		return ret;

	/* Determine number of locks */
	i = readl(io_base + SYSSTATUS_OFFSET);
	i >>= SPINLOCK_NUMLOCKS_BIT_OFFSET;

	/*
	 * runtime PM will make sure the clock of this module is
	 * enabled again iff at least one lock is requested
	 */
	ret = pm_runtime_put(&pdev->dev);
	if (ret < 0)
		return ret;

	/* one of the four lsb's must be set, and nothing else */
	if (hweight_long(i & 0xf) != 1 || i > 8)
		return -EINVAL;

	num_locks = i * 32; /* actual number of locks in this device */

	bank = devm_kzalloc(&pdev->dev, struct_size(bank, lock, num_locks),
			    GFP_KERNEL);
	if (!bank)
		return -ENOMEM;

	for (i = 0; i < num_locks; i++)
		bank->lock[i].priv = io_base + LOCK_BASE_OFFSET + sizeof(u32) * i;

	return devm_hwspin_lock_register(&pdev->dev, bank, &omap_hwspinlock_ops,
						base_id, num_locks);
}

static const struct of_device_id omap_hwspinlock_of_match[] = {
	{ .compatible = "ti,omap4-hwspinlock", },
	{ .compatible = "ti,am64-hwspinlock", },
	{ .compatible = "ti,am654-hwspinlock", },
	{ /* end */ },
};
MODULE_DEVICE_TABLE(of, omap_hwspinlock_of_match);

static struct platform_driver omap_hwspinlock_driver = {
	.probe		= omap_hwspinlock_probe,
	.driver		= {
		.name	= "omap_hwspinlock",
		.of_match_table = omap_hwspinlock_of_match,
	},
};

static int __init omap_hwspinlock_init(void)
{
	return platform_driver_register(&omap_hwspinlock_driver);
}
/* board init code might need to reserve hwspinlocks for predefined purposes */
postcore_initcall(omap_hwspinlock_init);

static void __exit omap_hwspinlock_exit(void)
{
	platform_driver_unregister(&omap_hwspinlock_driver);
}
module_exit(omap_hwspinlock_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hardware spinlock driver for OMAP");
MODULE_AUTHOR("Simon Que <sque@ti.com>");
MODULE_AUTHOR("Hari Kanigeri <h-kanigeri2@ti.com>");
MODULE_AUTHOR("Ohad Ben-Cohen <ohad@wizery.com>");
