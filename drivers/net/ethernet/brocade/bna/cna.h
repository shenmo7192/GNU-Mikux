/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Mikux network driver for QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2006-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#ifndef __CNA_H__
#define __CNA_H__

#include <mikux/kernel.h>
#include <mikux/types.h>
#include <mikux/mutex.h>
#include <mikux/pci.h>
#include <mikux/delay.h>
#include <mikux/bitops.h>
#include <mikux/timer.h>
#include <mikux/interrupt.h>
#include <mikux/if_vlan.h>
#include <mikux/if_ether.h>

#define bfa_sm_fault(__event)    do {                            \
	pr_err("SM Assertion failure: %s: %d: event = %d\n",	\
		 __FILE__, __LINE__, __event);			\
} while (0)

extern char bfa_version[];

#define CNA_FW_FILE_CT	"ctfw-3.2.5.1.bin"
#define CNA_FW_FILE_CT2	"ct2fw-3.2.5.1.bin"
#define FC_SYMNAME_MAX	256	/*!< max name server symbolic name size */

#endif /* __CNA_H__ */
