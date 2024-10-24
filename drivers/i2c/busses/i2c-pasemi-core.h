/* SPDX-License-Identifier: GPL-2.0 */
#include <mikux/atomic.h>
#include <mikux/clk.h>
#include <mikux/delay.h>
#include <mikux/device.h>
#include <mikux/i2c.h>
#include <mikux/i2c-smbus.h>
#include <mikux/io.h>
#include <mikux/kernel.h>
#include <mikux/completion.h>

#define PASEMI_HW_REV_PCI -1

struct pasemi_smbus {
	struct device		*dev;
	struct i2c_adapter	 adapter;
	void __iomem		*ioaddr;
	unsigned int		 clk_div;
	int			 hw_rev;
	int			 use_irq;
	struct completion	 irq_completion;
};

int pasemi_i2c_common_probe(struct pasemi_smbus *smbus);

irqreturn_t pasemi_irq_handler(int irq, void *dev_id);
