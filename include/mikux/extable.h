/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_EXTABLE_H
#define _MIKUX_EXTABLE_H

#include <mikux/stddef.h>	/* for NULL */
#include <mikux/types.h>

struct module;
struct exception_table_entry;

const struct exception_table_entry *
search_extable(const struct exception_table_entry *base,
	       const size_t num,
	       unsigned long value);
void sort_extable(struct exception_table_entry *start,
		  struct exception_table_entry *finish);
void sort_main_extable(void);
void trim_init_extable(struct module *m);

/* Given an address, look for it in the exception tables */
const struct exception_table_entry *search_exception_tables(unsigned long add);
const struct exception_table_entry *
search_kernel_exception_table(unsigned long addr);

#ifdef CONFIG_MODULES
/* For extable.c to search modules' exception tables. */
const struct exception_table_entry *search_module_extables(unsigned long addr);
#else
static inline const struct exception_table_entry *
search_module_extables(unsigned long addr)
{
	return NULL;
}
#endif /*CONFIG_MODULES*/

#ifdef CONFIG_BPF_JIT
const struct exception_table_entry *search_bpf_extables(unsigned long addr);
#else
static inline const struct exception_table_entry *
search_bpf_extables(unsigned long addr)
{
	return NULL;
}
#endif

#endif /* _MIKUX_EXTABLE_H */
