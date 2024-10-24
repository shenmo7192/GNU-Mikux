// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2012-2018 ARM Limited
 *
 * This supplies .note.* sections to go into the PT_NOTE inside the vDSO text.
 * Here we can supply some information useful to userland.
 */

#include <mikux/uts.h>
#include <mikux/version.h>
#include <mikux/elfnote.h>
#include <mikux/build-salt.h>

ELFNOTE32("Mikux", 0, MIKUX_VERSION_CODE);
BUILD_SALT;
