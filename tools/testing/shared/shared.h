/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __SHARED_H__
#define __SHARED_H__

#include <mikux/types.h>
#include <mikux/bug.h>
#include <mikux/kernel.h>
#include <mikux/bitops.h>

#include <mikux/gfp.h>
#include <mikux/rcupdate.h>

#ifndef module_init
#define module_init(x)
#endif

#ifndef module_exit
#define module_exit(x)
#endif

#ifndef MODULE_AUTHOR
#define MODULE_AUTHOR(x)
#endif

#ifndef MODULE_LICENSE
#define MODULE_LICENSE(x)
#endif

#ifndef MODULE_DESCRIPTION
#define MODULE_DESCRIPTION(x)
#endif

#ifndef dump_stack
#define dump_stack()	assert(0)
#endif

#endif /* __SHARED_H__ */
