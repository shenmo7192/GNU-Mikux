/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * This supplies .note.* sections to go into the PT_NOTE inside the vDSO text.
 * Here we can supply some information useful to userland.
 */

#include <mikux/elfnote.h>
#include <mikux/version.h>

ELFNOTE_START(Mikux, 0, "a")
	.long MIKUX_VERSION_CODE
ELFNOTE_END
