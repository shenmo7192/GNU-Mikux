// SPDX-License-Identifier: GPL-2.0
#include <mikux/acpi.h>
#include <mikux/cpu.h>
#include <mikux/cpumask.h>
#include <mikux/init.h>
#include <mikux/node.h>
#include <mikux/nodemask.h>
#include <mikux/percpu.h>
#include <asm/bootinfo.h>

#include <acpi/processor.h>

#ifdef CONFIG_HOTPLUG_CPU
bool arch_cpu_is_hotpluggable(int cpu)
{
	return !io_master(cpu);
}
#endif
