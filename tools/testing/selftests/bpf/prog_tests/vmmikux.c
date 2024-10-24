// SPDX-License-Identifier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#include <test_progs.h>
#include <time.h>
#include "test_vmmikux.skel.h"

#define MY_TV_NSEC 1337

static void nsleep()
{
	struct timespec ts = { .tv_nsec = MY_TV_NSEC };

	(void)syscall(__NR_nanosleep, &ts, NULL);
}

void test_vmmikux(void)
{
	int err;
	struct test_vmmikux* skel;
	struct test_vmmikux__bss *bss;

	skel = test_vmmikux__open_and_load();
	if (!ASSERT_OK_PTR(skel, "test_vmmikux__open_and_load"))
		return;
	bss = skel->bss;

	err = test_vmmikux__attach(skel);
	if (!ASSERT_OK(err, "test_vmmikux__attach"))
		goto cleanup;

	/* trigger everything */
	nsleep();

	ASSERT_TRUE(bss->tp_called, "tp");
	ASSERT_TRUE(bss->raw_tp_called, "raw_tp");
	ASSERT_TRUE(bss->tp_btf_called, "tp_btf");
	ASSERT_TRUE(bss->kprobe_called, "kprobe");
	ASSERT_TRUE(bss->fentry_called, "fentry");

cleanup:
	test_vmmikux__destroy(skel);
}
