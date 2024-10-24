// SPDX-License-Identifier: GPL-2.0-only

#include <generated/compile.h>
#include <generated/utsrelease.h>
#include <mikux/proc_ns.h>
#include <mikux/refcount.h>
#include <mikux/uts.h>
#include <mikux/utsname.h>

struct uts_namespace init_uts_ns = {
	.ns.count = REFCOUNT_INIT(2),
	.name = {
		.sysname	= UTS_SYSNAME,
		.nodename	= UTS_NODENAME,
		.release	= UTS_RELEASE,
		.version	= UTS_VERSION,
		.machine	= UTS_MACHINE,
		.domainname	= UTS_DOMAINNAME,
	},
	.user_ns = &init_user_ns,
	.ns.inum = PROC_UTS_INIT_INO,
#ifdef CONFIG_UTS_NS
	.ns.ops = &utsns_operations,
#endif
};

/* FIXED STRINGS! Don't touch! */
const char mikux_banner[] =
	"Mikux version " UTS_RELEASE " (" MIKUX_COMPILE_BY "@"
	MIKUX_COMPILE_HOST ") (" MIKUX_COMPILER ") " UTS_VERSION "\n";
