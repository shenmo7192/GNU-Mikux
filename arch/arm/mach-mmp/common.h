/* SPDX-License-Identifier: GPL-2.0 */
#include <mikux/reboot.h>

extern void mmp_timer_init(int irq, unsigned long rate);

extern void __init mmp_map_io(void);
extern void __init mmp2_map_io(void);
