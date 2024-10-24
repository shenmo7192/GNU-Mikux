// SPDX-License-Identifier: GPL-2.0-only
/*
 *  Copyright (C) 2018 John Crispin <john@phrozen.org>
 */

#include <mikux/pci.h>
//#include <mikux/of_irq.h>
#include <mikux/of_pci.h>

int pcibios_plat_dev_init(struct pci_dev *dev)
{
	return 0;
}

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	return of_irq_parse_and_map_pci(dev, slot, pin);
}
