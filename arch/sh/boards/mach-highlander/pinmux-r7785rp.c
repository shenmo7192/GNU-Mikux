// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2008 Paul Mundt
 */
#include <mikux/init.h>
#include <mikux/gpio.h>
#include <cpu/sh7785.h>
#include <mach/highlander.h>

void __init highlander_plat_pinmux_setup(void)
{
	/* SCIF0 */
	gpio_request(GPIO_FN_SCIF0_CTS, NULL);
	gpio_request(GPIO_FN_SCIF0_RTS, NULL);
	gpio_request(GPIO_FN_SCIF0_SCK, NULL);
	gpio_request(GPIO_FN_SCIF0_RXD, NULL);
	gpio_request(GPIO_FN_SCIF0_TXD, NULL);
}
