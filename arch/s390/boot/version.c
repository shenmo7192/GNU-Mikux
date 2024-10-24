// SPDX-License-Identifier: GPL-2.0
#include <generated/utsversion.h>
#include <generated/utsrelease.h>
#include <generated/compile.h>
#include "boot.h"

const char kernel_version[] = UTS_RELEASE
	" (" MIKUX_COMPILE_BY "@" MIKUX_COMPILE_HOST ") " UTS_VERSION;
