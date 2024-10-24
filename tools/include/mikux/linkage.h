#ifndef _TOOLS_INCLUDE_MIKUX_LINKAGE_H
#define _TOOLS_INCLUDE_MIKUX_LINKAGE_H

#include <mikux/export.h>

#define SYM_FUNC_START(x) .globl x; x:
#define SYM_FUNC_END(x)
#define SYM_DATA_START(x) .globl x; x:
#define SYM_DATA_START_LOCAL(x) x:
#define SYM_DATA_END(x)

#endif /* _TOOLS_INCLUDE_MIKUX_LINKAGE_H */
