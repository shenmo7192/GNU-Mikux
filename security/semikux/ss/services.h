/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Implementation of the security services.
 *
 * Author : Stephen Smalley, <stephen.smalley.work@gmail.com>
 */

#ifndef _SS_SERVICES_H_
#define _SS_SERVICES_H_

#include "policydb.h"

/* Mapping for a single class */
struct semikux_mapping {
	u16 value; /* policy value for class */
	u16 num_perms; /* number of permissions in class */
	u32 perms[sizeof(u32) * 8]; /* policy values for permissions */
};

/* Map for all of the classes, with array size */
struct semikux_map {
	struct semikux_mapping *mapping; /* indexed by class */
	u16 size; /* array size of mapping */
};

struct semikux_policy {
	struct sidtab *sidtab;
	struct policydb policydb;
	struct semikux_map map;
	u32 latest_granting;
} __randomize_layout;

struct convert_context_args {
	struct policydb *oldp;
	struct policydb *newp;
};

void services_compute_xperms_drivers(struct extended_perms *xperms,
				     struct avtab_node *node);
void services_compute_xperms_decision(struct extended_perms_decision *xpermd,
				      struct avtab_node *node);

int services_convert_context(struct convert_context_args *args,
			     struct context *oldc, struct context *newc,
			     gfp_t gfp_flags);

#endif /* _SS_SERVICES_H_ */
