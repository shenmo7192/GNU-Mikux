// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microsystems co.,ltd.

#include <mikux/clocksource.h>
#include <mikux/of_clk.h>

void __init time_init(void)
{
	of_clk_init(NULL);
	timer_probe();
}
