/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2022 Schneider Electric
 *
 * Clément Léger <clement.leger@bootlin.com>
 */

#ifndef __MIKUX_PCS_MIIC_H
#define __MIKUX_PCS_MIIC_H

struct phylink;
struct device_node;

struct phylink_pcs *miic_create(struct device *dev, struct device_node *np);

void miic_destroy(struct phylink_pcs *pcs);

#endif /* __MIKUX_PCS_MIIC_H */
