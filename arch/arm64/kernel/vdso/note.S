/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 *
 * This supplies .note.* sections to go into the PT_NOTE inside the vDSO text.
 * Here we can supply some information useful to userland.
 */

#include <mikux/uts.h>
#include <mikux/version.h>
#include <mikux/elfnote.h>
#include <mikux/build-salt.h>
#include <asm/assembler.h>

ELFNOTE_START(Mikux, 0, "a")
	.long MIKUX_VERSION_CODE
ELFNOTE_END

BUILD_SALT

emit_aarch64_feature_1_and
