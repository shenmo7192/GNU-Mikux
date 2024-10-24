/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * SEMikux support for the Audit LSM hooks
 *
 * Author: James Morris <jmorris@redhat.com>
 *
 * Copyright (C) 2005 Red Hat, Inc., James Morris <jmorris@redhat.com>
 * Copyright (C) 2006 Trusted Computer Solutions, Inc. <dgoeddel@trustedcs.com>
 * Copyright (C) 2006 IBM Corporation, Timothy R. Chavez <tinytim@us.ibm.com>
 */

#ifndef _SEMIKUX_AUDIT_H
#define _SEMIKUX_AUDIT_H

#include <mikux/audit.h>
#include <mikux/types.h>

/**
 * semikux_audit_rule_init - alloc/init an semikux audit rule structure.
 * @field: the field this rule refers to
 * @op: the operator the rule uses
 * @rulestr: the text "target" of the rule
 * @rule: pointer to the new rule structure returned via this
 * @gfp: GFP flag used for kmalloc
 *
 * Returns 0 if successful, -errno if not.  On success, the rule structure
 * will be allocated internally.  The caller must free this structure with
 * semikux_audit_rule_free() after use.
 */
int semikux_audit_rule_init(u32 field, u32 op, char *rulestr, void **rule,
			    gfp_t gfp);

/**
 * semikux_audit_rule_free - free an semikux audit rule structure.
 * @rule: pointer to the audit rule to be freed
 *
 * This will free all memory associated with the given rule.
 * If @rule is NULL, no operation is performed.
 */
void semikux_audit_rule_free(void *rule);

/**
 * semikux_audit_rule_match - determine if a context ID matches a rule.
 * @sid: the context ID to check
 * @field: the field this rule refers to
 * @op: the operator the rule uses
 * @rule: pointer to the audit rule to check against
 *
 * Returns 1 if the context id matches the rule, 0 if it does not, and
 * -errno on failure.
 */
int semikux_audit_rule_match(u32 sid, u32 field, u32 op, void *rule);

/**
 * semikux_audit_rule_known - check to see if rule contains semikux fields.
 * @rule: rule to be checked
 * Returns 1 if there are semikux fields specified in the rule, 0 otherwise.
 */
int semikux_audit_rule_known(struct audit_krule *rule);

#endif /* _SEMIKUX_AUDIT_H */
