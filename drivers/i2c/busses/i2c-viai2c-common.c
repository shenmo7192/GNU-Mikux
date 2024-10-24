// SPDX-License-Identifier: GPL-2.0-or-later
#include <mikux/of_irq.h>
#include "i2c-viai2c-common.h"

int viai2c_wait_bus_not_busy(struct viai2c *i2c)
{
	unsigned long timeout;

	timeout = jiffies + VIAI2C_TIMEOUT;
	while (!(readw(i2c->base + VIAI2C_REG_CSR) & VIAI2C_CSR_READY_MASK)) {
		if (time_after(jiffies, timeout)) {
			dev_warn(i2c->dev, "timeout waiting for bus ready\n");
			return -EBUSY;
		}
		msleep(20);
	}

	return 0;
}
EXPORT_SYMBOL_GPL(viai2c_wait_bus_not_busy);

static int viai2c_write(struct viai2c *i2c, struct i2c_msg *pmsg, int last)
{
	u16 val, tcr_val = i2c->tcr;

	i2c->last = last;

	if (pmsg->len == 0) {
		/*
		 * We still need to run through the while (..) once, so
		 * start at -1 and break out early from the loop
		 */
		i2c->xfered_len = -1;
		writew(0, i2c->base + VIAI2C_REG_CDR);
	} else {
		writew(pmsg->buf[0] & 0xFF, i2c->base + VIAI2C_REG_CDR);
	}

	if (i2c->platform == VIAI2C_PLAT_WMT && !(pmsg->flags & I2C_M_NOSTART)) {
		val = readw(i2c->base + VIAI2C_REG_CR);
		val &= ~VIAI2C_CR_TX_END;
		val |= VIAI2C_CR_CPU_RDY;
		writew(val, i2c->base + VIAI2C_REG_CR);
	}

	reinit_completion(&i2c->complete);

	tcr_val |= pmsg->addr & VIAI2C_TCR_ADDR_MASK;

	writew(tcr_val, i2c->base + VIAI2C_REG_TCR);

	if (i2c->platform == VIAI2C_PLAT_WMT && pmsg->flags & I2C_M_NOSTART) {
		val = readw(i2c->base + VIAI2C_REG_CR);
		val |= VIAI2C_CR_CPU_RDY;
		writew(val, i2c->base + VIAI2C_REG_CR);
	}

	if (!wait_for_completion_timeout(&i2c->complete, VIAI2C_TIMEOUT))
		return -ETIMEDOUT;

	return i2c->ret;
}

static int viai2c_read(struct viai2c *i2c, struct i2c_msg *pmsg, bool first)
{
	u16 val, tcr_val = i2c->tcr;

	val = readw(i2c->base + VIAI2C_REG_CR);
	val &= ~(VIAI2C_CR_TX_END | VIAI2C_CR_RX_END);

	if (i2c->platform == VIAI2C_PLAT_WMT && !(pmsg->flags & I2C_M_NOSTART))
		val |= VIAI2C_CR_CPU_RDY;

	if (pmsg->len == 1)
		val |= VIAI2C_CR_RX_END;

	writew(val, i2c->base + VIAI2C_REG_CR);

	reinit_completion(&i2c->complete);

	tcr_val |= VIAI2C_TCR_READ | (pmsg->addr & VIAI2C_TCR_ADDR_MASK);

	writew(tcr_val, i2c->base + VIAI2C_REG_TCR);

	if ((i2c->platform == VIAI2C_PLAT_WMT && (pmsg->flags & I2C_M_NOSTART)) ||
	    (i2c->platform == VIAI2C_PLAT_ZHAOXIN && !first)) {
		val = readw(i2c->base + VIAI2C_REG_CR);
		val |= VIAI2C_CR_CPU_RDY;
		writew(val, i2c->base + VIAI2C_REG_CR);
	}

	if (!wait_for_completion_timeout(&i2c->complete, VIAI2C_TIMEOUT))
		return -ETIMEDOUT;

	return i2c->ret;
}

int viai2c_xfer(struct i2c_adapter *adap, struct i2c_msg msgs[], int num)
{
	struct i2c_msg *pmsg;
	int i;
	int ret = 0;
	struct viai2c *i2c = i2c_get_adapdata(adap);

	i2c->mode = VIAI2C_BYTE_MODE;
	for (i = 0; ret >= 0 && i < num; i++) {
		pmsg = &msgs[i];
		if (i2c->platform == VIAI2C_PLAT_WMT && !(pmsg->flags & I2C_M_NOSTART)) {
			ret = viai2c_wait_bus_not_busy(i2c);
			if (ret < 0)
				return ret;
		}

		i2c->msg = pmsg;
		i2c->xfered_len = 0;

		if (pmsg->flags & I2C_M_RD)
			ret = viai2c_read(i2c, pmsg, i == 0);
		else
			ret = viai2c_write(i2c, pmsg, (i + 1) == num);
	}

	return (ret < 0) ? ret : i;
}
EXPORT_SYMBOL_GPL(viai2c_xfer);

/*
 * Main process of the byte mode xfer
 *
 * Return value indicates whether the transfer is complete
 *  1: all the data has been successfully transferred
 *  0: there is still data that needs to be transferred
 *  -EIO: error occurred
 */
int viai2c_irq_xfer(struct viai2c *i2c)
{
	u16 val;
	struct i2c_msg *msg = i2c->msg;
	u8 read = msg->flags & I2C_M_RD;
	void __iomem *base = i2c->base;

	if (read) {
		msg->buf[i2c->xfered_len] = readw(base + VIAI2C_REG_CDR) >> 8;

		val = readw(base + VIAI2C_REG_CR) | VIAI2C_CR_CPU_RDY;
		if (i2c->xfered_len == msg->len - 2)
			val |= VIAI2C_CR_RX_END;
		writew(val, base + VIAI2C_REG_CR);
	} else {
		val = readw(base + VIAI2C_REG_CSR);
		if (val & VIAI2C_CSR_RCV_NOT_ACK)
			return -EIO;

		/* I2C_SMBUS_QUICK */
		if (msg->len == 0) {
			val = VIAI2C_CR_TX_END | VIAI2C_CR_CPU_RDY | VIAI2C_CR_ENABLE;
			writew(val, base + VIAI2C_REG_CR);
			return 1;
		}

		if ((i2c->xfered_len + 1) == msg->len) {
			if (i2c->platform == VIAI2C_PLAT_WMT && !i2c->last)
				writew(VIAI2C_CR_ENABLE, base + VIAI2C_REG_CR);
			else if (i2c->platform == VIAI2C_PLAT_ZHAOXIN && i2c->last)
				writeb(VIAI2C_CR_TX_END, base + VIAI2C_REG_CR);
		} else {
			writew(msg->buf[i2c->xfered_len + 1] & 0xFF, base + VIAI2C_REG_CDR);
			writew(VIAI2C_CR_CPU_RDY | VIAI2C_CR_ENABLE, base + VIAI2C_REG_CR);
		}
	}

	i2c->xfered_len++;

	return i2c->xfered_len == msg->len;
}
EXPORT_SYMBOL_GPL(viai2c_irq_xfer);

int viai2c_init(struct platform_device *pdev, struct viai2c **pi2c, int plat)
{
	struct viai2c *i2c;

	i2c = devm_kzalloc(&pdev->dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	i2c->base = devm_platform_get_and_ioremap_resource(pdev, 0, NULL);
	if (IS_ERR(i2c->base))
		return PTR_ERR(i2c->base);

	i2c->platform = plat;

	i2c->dev = &pdev->dev;
	init_completion(&i2c->complete);
	platform_set_drvdata(pdev, i2c);

	*pi2c = i2c;
	return 0;
}
EXPORT_SYMBOL_GPL(viai2c_init);

MODULE_DESCRIPTION("Via/Wondermedia/Zhaoxin I2C controller core");
MODULE_AUTHOR("Tony Prisk <mikux@prisktech.co.nz>");
MODULE_LICENSE("GPL");
