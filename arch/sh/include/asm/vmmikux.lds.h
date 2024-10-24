/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_SH_VMMIKUX_LDS_H
#define __ASM_SH_VMMIKUX_LDS_H

#include <asm-generic/vmmikux.lds.h>

#ifdef CONFIG_DWARF_UNWINDER
#define DWARF_EH_FRAME							\
	.eh_frame : AT(ADDR(.eh_frame) - LOAD_OFFSET) {			\
		  __start_eh_frame = .;					\
		  *(.eh_frame)						\
		  __stop_eh_frame = .;					\
	}
#else
#define DWARF_EH_FRAME
#endif

#endif /* __ASM_SH_VMMIKUX_LDS_H */
