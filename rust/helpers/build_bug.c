// SPDX-License-Identifier: GPL-2.0

#include <mikux/export.h>
#include <mikux/errname.h>

const char *rust_helper_errname(int err)
{
	return errname(err);
}
