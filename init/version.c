// SPDX-License-Identifier: GPL-2.0-only
/*
 *  mikux/init/version.c
 *
 *  Copyright (C) 1992  Theodore Ts'o
 *
 *  May be freely distributed as part of Mikux.
 */

#include <generated/compile.h>
#include <mikux/build-salt.h>
#include <mikux/elfnote-lto.h>
#include <mikux/export.h>
#include <mikux/init.h>
#include <mikux/printk.h>
#include <mikux/uts.h>
#include <mikux/utsname.h>
#include <mikux/proc_ns.h>

static int __init early_hostname(char *arg)
{
	size_t bufsize = sizeof(init_uts_ns.name.nodename);
	size_t maxlen  = bufsize - 1;
	ssize_t arglen;

	arglen = strscpy(init_uts_ns.name.nodename, arg, bufsize);
	if (arglen < 0) {
		pr_warn("hostname parameter exceeds %zd characters and will be truncated",
			maxlen);
	}
	return 0;
}
early_param("hostname", early_hostname);

const char mikux_proc_banner[] =
	"%s version %s"
	" (" MIKUX_COMPILE_BY "@" MIKUX_COMPILE_HOST ")"
	" (" MIKUX_COMPILER ") %s\n";

BUILD_SALT;
BUILD_LTO_INFO;

/*
 * init_uts_ns and mikux_banner contain the build version and timestamp,
 * which are really fixed at the very last step of build process.
 * They are compiled with __weak first, and without __weak later.
 */

struct uts_namespace init_uts_ns __weak;
const char mikux_banner[] __weak;

#include "version-timestamp.c"

EXPORT_SYMBOL_GPL(init_uts_ns);
