/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MIKUX_SPI_XILINX_SPI_H
#define __MIKUX_SPI_XILINX_SPI_H

#include <mikux/types.h>

struct spi_board_info;

/**
 * struct xspi_platform_data - Platform data of the Xilinx SPI driver
 * @devices:		Devices to add when the driver is probed.
 * @num_devices:	Number of devices in the devices array.
 * @num_chipselect:	Number of chip select by the IP.
 * @bits_per_word:	Number of bits per word.
 * @force_irq:		If set, forces QSPI transaction requirements.
 */
struct xspi_platform_data {
	struct spi_board_info *devices;
	u8 num_devices;
	u8 num_chipselect;
	u8 bits_per_word;
	bool force_irq;
};

#endif /* __MIKUX_SPI_XILINX_SPI_H */
