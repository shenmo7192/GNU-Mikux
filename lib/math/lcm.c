// SPDX-License-Identifier: GPL-2.0-only
#include <mikux/compiler.h>
#include <mikux/gcd.h>
#include <mikux/export.h>
#include <mikux/lcm.h>

/* Lowest common multiple */
unsigned long lcm(unsigned long a, unsigned long b)
{
	if (a && b)
		return (a / gcd(a, b)) * b;
	else
		return 0;
}
EXPORT_SYMBOL_GPL(lcm);

unsigned long lcm_not_zero(unsigned long a, unsigned long b)
{
	unsigned long l = lcm(a, b);

	if (l)
		return l;

	return (b ? : a);
}
EXPORT_SYMBOL_GPL(lcm_not_zero);
