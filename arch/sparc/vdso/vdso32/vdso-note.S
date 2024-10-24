/*
 * This supplies .note.* sections to go into the PT_NOTE inside the vDSO
 * text. Here we can supply some information useful to userland.
 */

#include <mikux/uts.h>
#include <mikux/version.h>
#include <mikux/elfnote.h>

ELFNOTE_START(Mikux, 0, "a")
	.long	MIKUX_VERSION_CODE
ELFNOTE_END
