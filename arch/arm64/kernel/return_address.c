// SPDX-License-Identifier: GPL-2.0-only
/*
 * arch/arm64/kernel/return_address.c
 *
 * Copyright (C) 2013 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 */

#include <mikux/export.h>
#include <mikux/ftrace.h>
#include <mikux/kprobes.h>
#include <mikux/stacktrace.h>

#include <asm/stack_pointer.h>

struct return_address_data {
	unsigned int level;
	void *addr;
};

static bool save_return_addr(void *d, unsigned long pc)
{
	struct return_address_data *data = d;

	if (!data->level) {
		data->addr = (void *)pc;
		return false;
	} else {
		--data->level;
		return true;
	}
}
NOKPROBE_SYMBOL(save_return_addr);

void *return_address(unsigned int level)
{
	struct return_address_data data;

	data.level = level + 2;
	data.addr = NULL;

	arch_stack_walk(save_return_addr, &data, current, NULL);

	if (!data.level)
		return data.addr;
	else
		return NULL;
}
EXPORT_SYMBOL_GPL(return_address);
NOKPROBE_SYMBOL(return_address);
