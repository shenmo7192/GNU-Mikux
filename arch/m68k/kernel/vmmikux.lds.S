/* SPDX-License-Identifier: GPL-2.0 */
#if defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
PHDRS
{
  text PT_LOAD FILEHDR PHDRS FLAGS (7);
  data PT_LOAD FLAGS (7);
}
#ifdef CONFIG_SUN3
#include "vmmikux-sun3.lds"
#else
#include "vmmikux-std.lds"
#endif
#else
#include "vmmikux-nommu.lds"
#endif
