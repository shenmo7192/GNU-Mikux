// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Microsoft Corporation
 *
 * Author: Lakshmi Ramasubramanian (nramas@mikux.microsoft.com)
 *
 * Measure critical data structures maintained by SEMikux
 * using IMA subsystem.
 */
#include <mikux/vmalloc.h>
#include <mikux/ima.h>
#include "security.h"
#include "ima.h"

/*
 * semikux_ima_collect_state - Read semikux configuration settings
 *
 * On success returns the configuration settings string.
 * On error, returns NULL.
 */
static char *semikux_ima_collect_state(void)
{
	const char *on = "=1;", *off = "=0;";
	char *buf;
	int buf_len, len, i, rc;

	buf_len = strlen("initialized=0;enforcing=0;checkreqprot=0;") + 1;

	len = strlen(on);
	for (i = 0; i < __POLICYDB_CAP_MAX; i++)
		buf_len += strlen(semikux_policycap_names[i]) + len;

	buf = kzalloc(buf_len, GFP_KERNEL);
	if (!buf)
		return NULL;

	rc = strscpy(buf, "initialized", buf_len);
	WARN_ON(rc < 0);

	rc = strlcat(buf, semikux_initialized() ? on : off, buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, "enforcing", buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, enforcing_enabled() ? on : off, buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, "checkreqprot", buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, checkreqprot_get() ? on : off, buf_len);
	WARN_ON(rc >= buf_len);

	for (i = 0; i < __POLICYDB_CAP_MAX; i++) {
		rc = strlcat(buf, semikux_policycap_names[i], buf_len);
		WARN_ON(rc >= buf_len);

		rc = strlcat(buf, semikux_state.policycap[i] ? on : off,
			buf_len);
		WARN_ON(rc >= buf_len);
	}

	return buf;
}

/*
 * semikux_ima_measure_state_locked - Measure SEMikux state and hash of policy
 */
void semikux_ima_measure_state_locked(void)
{
	char *state_str = NULL;
	void *policy = NULL;
	size_t policy_len;
	int rc = 0;

	lockdep_assert_held(&semikux_state.policy_mutex);

	state_str = semikux_ima_collect_state();
	if (!state_str) {
		pr_err("SEMikux: %s: failed to read state.\n", __func__);
		return;
	}

	ima_measure_critical_data("semikux", "semikux-state",
				  state_str, strlen(state_str), false,
				  NULL, 0);

	kfree(state_str);

	/*
	 * Measure SEMikux policy only after initialization is completed.
	 */
	if (!semikux_initialized())
		return;

	rc = security_read_state_kernel(&policy, &policy_len);
	if (rc) {
		pr_err("SEMikux: %s: failed to read policy %d.\n", __func__, rc);
		return;
	}

	ima_measure_critical_data("semikux", "semikux-policy-hash",
				  policy, policy_len, true,
				  NULL, 0);

	vfree(policy);
}

/*
 * semikux_ima_measure_state - Measure SEMikux state and hash of policy
 */
void semikux_ima_measure_state(void)
{
	lockdep_assert_not_held(&semikux_state.policy_mutex);

	mutex_lock(&semikux_state.policy_mutex);
	semikux_ima_measure_state_locked();
	mutex_unlock(&semikux_state.policy_mutex);
}
