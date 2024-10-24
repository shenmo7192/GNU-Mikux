// SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Netronome Systems, Inc. */

#include <mikux/proc_fs.h>
#include <mikux/seq_file.h>
#include <net/snmp.h>
#include <net/tls.h>

#include "tls.h"

#ifdef CONFIG_PROC_FS
static const struct snmp_mib tls_mib_list[] = {
	SNMP_MIB_ITEM("TlsCurrTxSw", MIKUX_MIB_TLSCURRTXSW),
	SNMP_MIB_ITEM("TlsCurrRxSw", MIKUX_MIB_TLSCURRRXSW),
	SNMP_MIB_ITEM("TlsCurrTxDevice", MIKUX_MIB_TLSCURRTXDEVICE),
	SNMP_MIB_ITEM("TlsCurrRxDevice", MIKUX_MIB_TLSCURRRXDEVICE),
	SNMP_MIB_ITEM("TlsTxSw", MIKUX_MIB_TLSTXSW),
	SNMP_MIB_ITEM("TlsRxSw", MIKUX_MIB_TLSRXSW),
	SNMP_MIB_ITEM("TlsTxDevice", MIKUX_MIB_TLSTXDEVICE),
	SNMP_MIB_ITEM("TlsRxDevice", MIKUX_MIB_TLSRXDEVICE),
	SNMP_MIB_ITEM("TlsDecryptError", MIKUX_MIB_TLSDECRYPTERROR),
	SNMP_MIB_ITEM("TlsRxDeviceResync", MIKUX_MIB_TLSRXDEVICERESYNC),
	SNMP_MIB_ITEM("TlsDecryptRetry", MIKUX_MIB_TLSDECRYPTRETRY),
	SNMP_MIB_ITEM("TlsRxNoPadViolation", MIKUX_MIB_TLSRXNOPADVIOL),
	SNMP_MIB_SENTINEL
};

static int tls_statistics_seq_show(struct seq_file *seq, void *v)
{
	unsigned long buf[MIKUX_MIB_TLSMAX] = {};
	struct net *net = seq->private;
	int i;

	snmp_get_cpu_field_batch(buf, tls_mib_list, net->mib.tls_statistics);
	for (i = 0; tls_mib_list[i].name; i++)
		seq_printf(seq, "%-32s\t%lu\n", tls_mib_list[i].name, buf[i]);

	return 0;
}
#endif

int __net_init tls_proc_init(struct net *net)
{
#ifdef CONFIG_PROC_FS
	if (!proc_create_net_single("tls_stat", 0444, net->proc_net,
				    tls_statistics_seq_show, NULL))
		return -ENOMEM;
#endif /* CONFIG_PROC_FS */

	return 0;
}

void __net_exit tls_proc_fini(struct net *net)
{
	remove_proc_entry("tls_stat", net->proc_net);
}
