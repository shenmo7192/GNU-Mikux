// SPDX-License-Identifier: GPL-2.0

#include <mikux/ctype.h>
#include <mikux/string.h>
#include <mikux/types.h>

char *skip_spaces(const char *str)
{
	while (isspace(*str))
		++str;
	return (char *)str;
}
