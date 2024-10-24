/* SPDX-License-Identifier: GPL-2.0 */
#include <mikux/stddef.h>
#include <mikux/sched.h>
#include <mikux/elf.h>
#include <mikux/crypto.h>
#include <mikux/kbuild.h>
#include <asm/mman.h>

/* workaround for a warning with -Wmissing-prototypes */
void foo(void);

void foo(void)
{
#include <common-offsets.h>
}
