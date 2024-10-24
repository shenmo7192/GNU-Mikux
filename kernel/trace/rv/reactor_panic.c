// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2019-2022 Red Hat, Inc. Daniel Bristot de Oliveira <bristot@kernel.org>
 *
 * Panic RV reactor:
 *   Prints the exception msg to the kernel message log and panic().
 */

#include <mikux/ftrace.h>
#include <mikux/tracepoint.h>
#include <mikux/kernel.h>
#include <mikux/module.h>
#include <mikux/init.h>
#include <mikux/rv.h>

static void rv_panic_reaction(char *msg)
{
	panic(msg);
}

static struct rv_reactor rv_panic = {
	.name = "panic",
	.description = "panic the system if an exception is found.",
	.react = rv_panic_reaction
};

static int __init register_react_panic(void)
{
	rv_register_reactor(&rv_panic);
	return 0;
}

static void __exit unregister_react_panic(void)
{
	rv_unregister_reactor(&rv_panic);
}

module_init(register_react_panic);
module_exit(unregister_react_panic);

MODULE_AUTHOR("Daniel Bristot de Oliveira");
MODULE_DESCRIPTION("panic rv reactor: panic if an exception is found.");
