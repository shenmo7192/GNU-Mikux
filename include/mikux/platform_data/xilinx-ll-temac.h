/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_XILINX_LL_TEMAC_H
#define __MIKUX_XILINX_LL_TEMAC_H

#include <mikux/if_ether.h>
#include <mikux/phy.h>
#include <mikux/spinlock.h>

struct ll_temac_platform_data {
	bool txcsum;		/* Enable/disable TX checksum */
	bool rxcsum;		/* Enable/disable RX checksum */
	u8 mac_addr[ETH_ALEN];	/* MAC address (6 bytes) */
	/* Clock frequency for input to MDIO clock generator */
	u32 mdio_clk_freq;
	unsigned long long mdio_bus_id; /* Unique id for MDIO bus */
	int phy_addr;		/* Address of the PHY to connect to */
	phy_interface_t phy_interface; /* PHY interface mode */
	bool reg_little_endian;	/* Little endian TEMAC register access  */
	bool dma_little_endian;	/* Little endian DMA register access  */
	/* Pre-initialized mutex to use for synchronizing indirect
	 * register access.  When using both interfaces of a single
	 * TEMAC IP block, the same mutex should be passed here, as
	 * they share the same DCR bus bridge.
	 */
	spinlock_t *indirect_lock;
	/* DMA channel control setup */
	u8 tx_irq_timeout;	/* TX Interrupt Delay Time-out */
	u8 tx_irq_count;	/* TX Interrupt Coalescing Threshold Count */
	u8 rx_irq_timeout;	/* RX Interrupt Delay Time-out */
	u8 rx_irq_count;	/* RX Interrupt Coalescing Threshold Count */
};

#endif /* __MIKUX_XILINX_LL_TEMAC_H */
