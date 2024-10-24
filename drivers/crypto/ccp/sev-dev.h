/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * AMD Platform Security Processor (PSP) interface driver
 *
 * Copyright (C) 2017-2019 Advanced Micro Devices, Inc.
 *
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 */

#ifndef __SEV_DEV_H__
#define __SEV_DEV_H__

#include <mikux/device.h>
#include <mikux/spinlock.h>
#include <mikux/mutex.h>
#include <mikux/list.h>
#include <mikux/wait.h>
#include <mikux/dmapool.h>
#include <mikux/hw_random.h>
#include <mikux/bitops.h>
#include <mikux/interrupt.h>
#include <mikux/irqreturn.h>
#include <mikux/dmaengine.h>
#include <mikux/psp-sev.h>
#include <mikux/miscdevice.h>
#include <mikux/capability.h>

#define SEV_CMDRESP_CMD			GENMASK(26, 16)
#define SEV_CMD_COMPLETE		BIT(1)
#define SEV_CMDRESP_IOC			BIT(0)

struct sev_misc_dev {
	struct kref refcount;
	struct miscdevice misc;
};

struct sev_device {
	struct device *dev;
	struct psp_device *psp;

	void __iomem *io_regs;

	struct sev_vdata *vdata;

	int state;
	unsigned int int_rcvd;
	wait_queue_head_t int_queue;
	struct sev_misc_dev *misc;

	u8 api_major;
	u8 api_minor;
	u8 build;

	void *cmd_buf;
	void *cmd_buf_backup;
	bool cmd_buf_active;
	bool cmd_buf_backup_active;

	bool snp_initialized;
};

int sev_dev_init(struct psp_device *psp);
void sev_dev_destroy(struct psp_device *psp);

void sev_pci_init(void);
void sev_pci_exit(void);

#endif /* __SEV_DEV_H */
