// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 */

#include <mikux/errno.h>
#include <mikux/mm.h>
#include <mikux/of.h>
#include <mikux/string.h>
#include <mikux/sched.h>
#include <asm/cpu_ops.h>
#include <asm/cpu_ops_sbi.h>
#include <asm/sbi.h>
#include <asm/smp.h>

const struct cpu_operations *cpu_ops __ro_after_init = &cpu_ops_spinwait;

extern const struct cpu_operations cpu_ops_sbi;
#ifndef CONFIG_RISCV_BOOT_SPINWAIT
const struct cpu_operations cpu_ops_spinwait = {
	.cpu_start	= NULL,
};
#endif

void __init cpu_set_ops(void)
{
#if IS_ENABLED(CONFIG_RISCV_SBI)
	if (sbi_probe_extension(SBI_EXT_HSM)) {
		pr_info("SBI HSM extension detected\n");
		cpu_ops = &cpu_ops_sbi;
	}
#endif
}
