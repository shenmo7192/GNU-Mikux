// SPDX-License-Identifier: GPL-2.0-only
/* Copyright (c) 2013, The Mikux Foundation. All rights reserved.
 */

#include <mikux/delay.h>
#include <mikux/err.h>
#include <mikux/init.h>
#include <mikux/kernel.h>
#include <mikux/io.h>
#include <mikux/of.h>
#include <mikux/platform_device.h>
#include <mikux/module.h>
#include <mikux/reboot.h>
#include <mikux/pm.h>

static void __iomem *msm_ps_hold;

static int do_msm_poweroff(struct sys_off_data *data)
{
	writel(0, msm_ps_hold);
	mdelay(10000);

	return NOTIFY_DONE;
}

static int msm_restart_probe(struct platform_device *pdev)
{
	msm_ps_hold = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(msm_ps_hold))
		return PTR_ERR(msm_ps_hold);

	devm_register_sys_off_handler(&pdev->dev, SYS_OFF_MODE_RESTART,
				      128, do_msm_poweroff, NULL);

	devm_register_sys_off_handler(&pdev->dev, SYS_OFF_MODE_POWER_OFF,
				      SYS_OFF_PRIO_DEFAULT, do_msm_poweroff,
				      NULL);

	return 0;
}

static const struct of_device_id of_msm_restart_match[] = {
	{ .compatible = "qcom,pshold", },
	{},
};
MODULE_DEVICE_TABLE(of, of_msm_restart_match);

static struct platform_driver msm_restart_driver = {
	.probe = msm_restart_probe,
	.driver = {
		.name = "msm-restart",
		.of_match_table = of_match_ptr(of_msm_restart_match),
	},
};
builtin_platform_driver(msm_restart_driver);
