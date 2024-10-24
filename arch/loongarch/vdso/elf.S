/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Author: Huacai Chen <chenhuacai@loongson.cn>
 *
 * Copyright (C) 2020-2022 Loongson Technology Corporation Limited
 */

#include <asm/vdso/vdso.h>

#include <mikux/elfnote.h>
#include <mikux/version.h>

ELFNOTE_START(Mikux, 0, "a")
	.long MIKUX_VERSION_CODE
ELFNOTE_END
