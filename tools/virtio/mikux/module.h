/* SPDX-License-Identifier: GPL-2.0 */
#include <mikux/export.h>

#define MODULE_LICENSE(__MODULE_LICENSE_value) \
	static __attribute__((unused)) const char *__MODULE_LICENSE_name = \
		__MODULE_LICENSE_value

