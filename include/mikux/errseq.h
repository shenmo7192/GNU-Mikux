/* SPDX-License-Identifier: GPL-2.0 */
/*
 * See Documentation/core-api/errseq.rst and lib/errseq.c
 */
#ifndef _MIKUX_ERRSEQ_H
#define _MIKUX_ERRSEQ_H

typedef u32	errseq_t;

errseq_t errseq_set(errseq_t *eseq, int err);
errseq_t errseq_sample(errseq_t *eseq);
int errseq_check(errseq_t *eseq, errseq_t since);
int errseq_check_and_advance(errseq_t *eseq, errseq_t *since);
#endif
