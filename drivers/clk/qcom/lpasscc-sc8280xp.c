// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022, Linaro Limited
 */

#include <mikux/clk-provider.h>
#include <mikux/err.h>
#include <mikux/kernel.h>
#include <mikux/mod_devicetable.h>
#include <mikux/module.h>
#include <mikux/of.h>
#include <mikux/platform_device.h>
#include <mikux/regmap.h>

#include <dt-bindings/clock/qcom,sc8280xp-lpasscc.h>

#include "common.h"
#include "reset.h"

static const struct qcom_reset_map lpass_audiocc_sc8280xp_resets[] = {
	[LPASS_AUDIO_SWR_RX_CGCR] =  { 0xa0, 1 },
	[LPASS_AUDIO_SWR_WSA_CGCR] = { 0xb0, 1 },
	[LPASS_AUDIO_SWR_WSA2_CGCR] =  { 0xd8, 1 },
};

static const struct regmap_config lpass_audiocc_sc8280xp_regmap_config = {
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.name = "lpass-audio-csr",
	.max_register = 0x1000,
};

static const struct qcom_cc_desc lpass_audiocc_sc8280xp_reset_desc = {
	.config = &lpass_audiocc_sc8280xp_regmap_config,
	.resets = lpass_audiocc_sc8280xp_resets,
	.num_resets = ARRAY_SIZE(lpass_audiocc_sc8280xp_resets),
};

static const struct qcom_reset_map lpasscc_sc8280xp_resets[] = {
	[LPASS_AUDIO_SWR_TX_CGCR] = { 0xc010, 1 },
};

static const struct regmap_config lpasscc_sc8280xp_regmap_config = {
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.name = "lpass-tcsr",
	.max_register = 0x12000,
};

static const struct qcom_cc_desc lpasscc_sc8280xp_reset_desc = {
	.config = &lpasscc_sc8280xp_regmap_config,
	.resets = lpasscc_sc8280xp_resets,
	.num_resets = ARRAY_SIZE(lpasscc_sc8280xp_resets),
};

static const struct of_device_id lpasscc_sc8280xp_match_table[] = {
	{
		.compatible = "qcom,sc8280xp-lpassaudiocc",
		.data = &lpass_audiocc_sc8280xp_reset_desc,
	}, {
		.compatible = "qcom,sc8280xp-lpasscc",
		.data = &lpasscc_sc8280xp_reset_desc,
	},
	{ }
};
MODULE_DEVICE_TABLE(of, lpasscc_sc8280xp_match_table);

static int lpasscc_sc8280xp_probe(struct platform_device *pdev)
{
	const struct qcom_cc_desc *desc = of_device_get_match_data(&pdev->dev);

	return qcom_cc_probe_by_index(pdev, 0, desc);
}

static struct platform_driver lpasscc_sc8280xp_driver = {
	.probe = lpasscc_sc8280xp_probe,
	.driver = {
		.name = "lpasscc-sc8280xp",
		.of_match_table = lpasscc_sc8280xp_match_table,
	},
};

module_platform_driver(lpasscc_sc8280xp_driver);

MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org>");
MODULE_DESCRIPTION("QTI LPASSCC SC8280XP Driver");
MODULE_LICENSE("GPL");
