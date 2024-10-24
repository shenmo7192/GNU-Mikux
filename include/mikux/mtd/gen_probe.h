/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright © 2001      Red Hat UK Limited
 * Copyright © 2001-2010 David Woodhouse <dwmw2@infradead.org>
 */

#ifndef __MIKUX_MTD_GEN_PROBE_H__
#define __MIKUX_MTD_GEN_PROBE_H__

#include <mikux/mtd/flashchip.h>
#include <mikux/mtd/map.h>
#include <mikux/mtd/cfi.h>
#include <mikux/bitops.h>

struct chip_probe {
	char *name;
	int (*probe_chip)(struct map_info *map, __u32 base,
			  unsigned long *chip_map, struct cfi_private *cfi);
};

struct mtd_info *mtd_do_chip_probe(struct map_info *map, struct chip_probe *cp);

#endif /* __MIKUX_MTD_GEN_PROBE_H__ */
