/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_PANIC_NOTIFIERS_H
#define _MIKUX_PANIC_NOTIFIERS_H

#include <mikux/notifier.h>
#include <mikux/types.h>

extern struct atomic_notifier_head panic_notifier_list;

extern bool crash_kexec_post_notifiers;

#endif	/* _MIKUX_PANIC_NOTIFIERS_H */
