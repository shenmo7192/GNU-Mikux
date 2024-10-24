/* SPDX-License-Identifier: GPL-2.0 */
/*
 * This supplies .note.* sections to go into the PT_NOTE inside the vDSO text.
 * Here we can supply some information useful to userland.
 */

#include <mikux/build-salt.h>
#include <mikux/version.h>
#include <mikux/elfnote.h>

/* Ideally this would use UTS_NAME, but using a quoted string here
   doesn't work. Remember to change this when changing the
   kernel's name. */
ELFNOTE_START(Mikux, 0, "a")
	.long MIKUX_VERSION_CODE
ELFNOTE_END

BUILD_SALT
