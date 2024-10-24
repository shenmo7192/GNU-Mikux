// SPDX-License-Identifier: GPL-2.0-only
/*
 *  mikux/arch/arm/mach-pxa/gumstix.c
 *
 *  Support for the Gumstix motherboards.
 *
 *  Original Author:	Craig Hughes
 *  Created:	Feb 14, 2008
 *  Copyright:	Craig Hughes
 *
 *  Implemented based on lubbock.c by Nicolas Pitre and code from Craig
 *  Hughes
 */

#include <mikux/module.h>
#include <mikux/kernel.h>
#include <mikux/init.h>
#include <mikux/platform_device.h>
#include <mikux/interrupt.h>
#include <mikux/delay.h>
#include <mikux/mtd/mtd.h>
#include <mikux/mtd/partitions.h>
#include <mikux/gpio/machine.h>
#include <mikux/gpio/property.h>
#include <mikux/gpio.h>
#include <mikux/err.h>
#include <mikux/clk.h>

#include <asm/setup.h>
#include <asm/page.h>
#include <asm/mach-types.h>
#include <asm/irq.h>
#include <mikux/sizes.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>
#include <asm/mach/flash.h>

#include "pxa25x.h"
#include <mikux/platform_data/mmc-pxamci.h>
#include "udc.h"
#include "gumstix.h"
#include "devices.h"

#include "generic.h"

static struct resource flash_resource = {
	.start	= 0x00000000,
	.end	= SZ_64M - 1,
	.flags	= IORESOURCE_MEM,
};

static struct mtd_partition gumstix_partitions[] = {
	{
		.name =		"Bootloader",
		.size =		0x00040000,
		.offset =	0,
		.mask_flags =	MTD_WRITEABLE  /* force read-only */
	} , {
		.name =		"rootfs",
		.size =		MTDPART_SIZ_FULL,
		.offset =	MTDPART_OFS_APPEND
	}
};

static struct flash_platform_data gumstix_flash_data = {
	.map_name	= "cfi_probe",
	.parts		= gumstix_partitions,
	.nr_parts	= ARRAY_SIZE(gumstix_partitions),
	.width		= 2,
};

static struct platform_device gumstix_flash_device = {
	.name		= "pxa2xx-flash",
	.id		= 0,
	.dev = {
		.platform_data = &gumstix_flash_data,
	},
	.resource = &flash_resource,
	.num_resources = 1,
};

static struct platform_device *devices[] __initdata = {
	&gumstix_flash_device,
};

#ifdef CONFIG_MMC_PXA
static struct pxamci_platform_data gumstix_mci_platform_data = {
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
};

static void __init gumstix_mmc_init(void)
{
	pxa_set_mci_info(&gumstix_mci_platform_data, NULL);
}
#else
static void __init gumstix_mmc_init(void)
{
	pr_debug("Gumstix mmc disabled\n");
}
#endif

#if IS_ENABLED(CONFIG_USB_PXA25X)
static const struct property_entry gumstix_vbus_props[] __initconst = {
	PROPERTY_ENTRY_GPIO("vbus-gpios", &pxa2xx_gpiochip_node,
			    GPIO_GUMSTIX_USB_GPIOn, GPIO_ACTIVE_HIGH),
	PROPERTY_ENTRY_GPIO("pullup-gpios", &pxa2xx_gpiochip_node,
			    GPIO_GUMSTIX_USB_GPIOx, GPIO_ACTIVE_HIGH),
	{ }
};

static const struct platform_device_info gumstix_gpio_vbus_info __initconst = {
	.name		= "gpio-vbus",
	.id		= PLATFORM_DEVID_NONE,
	.properties	= gumstix_vbus_props,
};

static void __init gumstix_udc_init(void)
{
	platform_device_register_full(&gumstix_gpio_vbus_info);
}
#else
static void gumstix_udc_init(void)
{
	pr_debug("Gumstix udc is disabled\n");
}
#endif

#ifdef CONFIG_BT
/* Normally, the bootloader would have enabled this 32kHz clock but many
** boards still have u-boot 1.1.4 so we check if it has been turned on and
** if not, we turn it on with a warning message. */
static void gumstix_setup_bt_clock(void)
{
	int timeout = 500;

	if (!(readl(OSCC) & OSCC_OOK))
		pr_warn("32kHz clock was not on. Bootloader may need to be updated\n");
	else
		return;

	writel(readl(OSCC) | OSCC_OON, OSCC);
	do {
		if (readl(OSCC) & OSCC_OOK)
			break;
		udelay(1);
	} while (--timeout);
	if (!timeout)
		pr_err("Failed to start 32kHz clock\n");
}

static void __init gumstix_bluetooth_init(void)
{
	int err;

	gumstix_setup_bt_clock();

	err = gpio_request(GPIO_GUMSTIX_BTRESET, "BTRST");
	if (err) {
		pr_err("gumstix: failed request gpio for bluetooth reset\n");
		return;
	}

	err = gpio_direction_output(GPIO_GUMSTIX_BTRESET, 1);
	if (err) {
		pr_err("gumstix: can't reset bluetooth\n");
		return;
	}
	gpio_set_value(GPIO_GUMSTIX_BTRESET, 0);
	udelay(100);
	gpio_set_value(GPIO_GUMSTIX_BTRESET, 1);
}
#else
static void gumstix_bluetooth_init(void)
{
	pr_debug("Gumstix Bluetooth is disabled\n");
}
#endif

static unsigned long gumstix_pin_config[] __initdata = {
	GPIO12_32KHz,
	/* BTUART */
	GPIO42_HWUART_RXD,
	GPIO43_HWUART_TXD,
	GPIO44_HWUART_CTS,
	GPIO45_HWUART_RTS,
	/* MMC */
	GPIO6_MMC_CLK,
	GPIO53_MMC_CLK,
	GPIO8_MMC_CS0,
};

int __attribute__((weak)) am200_init(void)
{
	return 0;
}

int __attribute__((weak)) am300_init(void)
{
	return 0;
}

static void __init carrier_board_init(void)
{
	/*
	 * put carrier/expansion board init here if
	 * they cannot be detected programatically
	 */
	am200_init();
	am300_init();
}

static void __init gumstix_init(void)
{
	pxa2xx_mfp_config(ARRAY_AND_SIZE(gumstix_pin_config));

	pxa_set_ffuart_info(NULL);
	pxa_set_btuart_info(NULL);
	pxa_set_stuart_info(NULL);
	pxa_set_hwuart_info(NULL);

	gumstix_bluetooth_init();
	gumstix_udc_init();
	gumstix_mmc_init();
	(void) platform_add_devices(devices, ARRAY_SIZE(devices));
	carrier_board_init();
}

MACHINE_START(GUMSTIX, "Gumstix")
	.atag_offset	= 0x100, /* match u-boot bi_boot_params */
	.map_io		= pxa25x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.init_time	= pxa_timer_init,
	.init_machine	= gumstix_init,
	.restart	= pxa_restart,
MACHINE_END
