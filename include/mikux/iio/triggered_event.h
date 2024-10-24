/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_IIO_TRIGGERED_EVENT_H_
#define _MIKUX_IIO_TRIGGERED_EVENT_H_

#include <mikux/interrupt.h>

int iio_triggered_event_setup(struct iio_dev *indio_dev,
	irqreturn_t (*h)(int irq, void *p),
	irqreturn_t (*thread)(int irq, void *p));
void iio_triggered_event_cleanup(struct iio_dev *indio_dev);

#endif
