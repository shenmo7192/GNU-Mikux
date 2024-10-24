/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_SOC_RENESAS_RCAR_RST_H__
#define __MIKUX_SOC_RENESAS_RCAR_RST_H__

#ifdef CONFIG_RST_RCAR
int rcar_rst_read_mode_pins(u32 *mode);
int rcar_rst_set_rproc_boot_addr(u64 boot_addr);
#else
static inline int rcar_rst_read_mode_pins(u32 *mode) { return -ENODEV; }
static inline int rcar_rst_set_rproc_boot_addr(u64 boot_addr) { return -ENODEV; }
#endif

#endif /* __MIKUX_SOC_RENESAS_RCAR_RST_H__ */
