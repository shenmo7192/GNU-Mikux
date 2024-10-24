/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Timer handling
 */

#ifndef __CTTIMER_H
#define __CTTIMER_H

#include <mikux/spinlock.h>
#include <mikux/timer.h>
#include <mikux/list.h>

struct snd_pcm_substream;
struct ct_atc;
struct ct_atc_pcm;

struct ct_timer;
struct ct_timer_instance;

struct ct_timer *ct_timer_new(struct ct_atc *atc);
void ct_timer_free(struct ct_timer *atimer);

struct ct_timer_instance *
ct_timer_instance_new(struct ct_timer *atimer, struct ct_atc_pcm *apcm);
void ct_timer_instance_free(struct ct_timer_instance *ti);
void ct_timer_start(struct ct_timer_instance *ti);
void ct_timer_stop(struct ct_timer_instance *ti);
void ct_timer_prepare(struct ct_timer_instance *ti);

#endif /* __CTTIMER_H */
