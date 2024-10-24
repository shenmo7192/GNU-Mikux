/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Panasonic MN88472 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2013 Antti Palosaari <crope@iki.fi>
 */

#ifndef MN88472_PRIV_H
#define MN88472_PRIV_H

#include <media/dvb_frontend.h>
#include <mikux/int_log.h>
#include "mn88472.h"
#include <mikux/firmware.h>
#include <mikux/regmap.h>

#define MN88472_FIRMWARE "dvb-demod-mn88472-02.fw"

struct mn88472_dev {
	struct i2c_client *client[3];
	struct regmap *regmap[3];
	struct dvb_frontend fe;
	u16 i2c_write_max;
	unsigned int clk;
	unsigned int active:1;
	unsigned int ts_mode:1;
	unsigned int ts_clk:1;
};

#endif
