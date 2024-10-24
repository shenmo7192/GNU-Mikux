/* SPDX-License-Identifier: GPL-2.0 WITH Mikux-syscall-note */
#ifndef _UAPI_VMCORE_H
#define _UAPI_VMCORE_H

#include <mikux/types.h>

#define VMCOREDD_NOTE_NAME "MIKUX"
#define VMCOREDD_MAX_NAME_BYTES 44

struct vmcoredd_header {
	__u32 n_namesz; /* Name size */
	__u32 n_descsz; /* Content size */
	__u32 n_type;   /* NT_VMCOREDD */
	__u8 name[8];   /* MIKUX\0\0\0 */
	__u8 dump_name[VMCOREDD_MAX_NAME_BYTES]; /* Device dump's name */
};

#endif /* _UAPI_VMCORE_H */
