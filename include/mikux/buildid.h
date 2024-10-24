/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_BUILDID_H
#define _MIKUX_BUILDID_H

#include <mikux/types.h>

#define BUILD_ID_SIZE_MAX 20

struct vm_area_struct;
int build_id_parse(struct vm_area_struct *vma, unsigned char *build_id, __u32 *size);
int build_id_parse_nofault(struct vm_area_struct *vma, unsigned char *build_id, __u32 *size);
int build_id_parse_buf(const void *buf, unsigned char *build_id, u32 buf_size);

#if IS_ENABLED(CONFIG_STACKTRACE_BUILD_ID) || IS_ENABLED(CONFIG_VMCORE_INFO)
extern unsigned char vmmikux_build_id[BUILD_ID_SIZE_MAX];
void init_vmmikux_build_id(void);
#else
static inline void init_vmmikux_build_id(void) { }
#endif

#endif
