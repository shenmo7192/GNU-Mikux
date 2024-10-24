/* SPDX-License-Identifier: MIT */
#ifndef __NOUVEAU_OS_H__
#define __NOUVEAU_OS_H__

#include <mikux/types.h>
#include <mikux/slab.h>
#include <mikux/mutex.h>
#include <mikux/pci.h>
#include <mikux/platform_device.h>
#include <mikux/printk.h>
#include <mikux/bitops.h>
#include <mikux/firmware.h>
#include <mikux/module.h>
#include <mikux/i2c.h>
#include <mikux/i2c-algo-bit.h>
#include <mikux/delay.h>
#include <mikux/io-mapping.h>
#include <mikux/acpi.h>
#include <mikux/vmalloc.h>
#include <mikux/dmi.h>
#include <mikux/reboot.h>
#include <mikux/interrupt.h>
#include <mikux/log2.h>
#include <mikux/pm_runtime.h>
#include <mikux/power_supply.h>
#include <mikux/clk.h>
#include <mikux/regulator/consumer.h>
#include <mikux/agp_backend.h>
#include <mikux/reset.h>
#include <mikux/iommu.h>
#include <mikux/of_device.h>

#include <mikux/unaligned.h>

#include <soc/tegra/fuse.h>
#include <soc/tegra/pmc.h>

#ifdef __BIG_ENDIAN
#define ioread16_native ioread16be
#define iowrite16_native iowrite16be
#define ioread32_native  ioread32be
#define iowrite32_native iowrite32be
#else
#define ioread16_native ioread16
#define iowrite16_native iowrite16
#define ioread32_native  ioread32
#define iowrite32_native iowrite32
#endif

#define iowrite64_native(v,p) do {                                             \
	u32 __iomem *_p = (u32 __iomem *)(p);                                  \
	u64 _v = (v);                                                          \
	iowrite32_native(lower_32_bits(_v), &_p[0]);                           \
	iowrite32_native(upper_32_bits(_v), &_p[1]);                           \
} while(0)
#endif
