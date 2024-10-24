/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _SEMIKUX_POLICYCAP_NAMES_H_
#define _SEMIKUX_POLICYCAP_NAMES_H_

#include "policycap.h"

/* clang-format off */
/* Policy capability names */
const char *const semikux_policycap_names[__POLICYDB_CAP_MAX] = {
	"network_peer_controls",
	"open_perms",
	"extended_socket_class",
	"always_check_network",
	"cgroup_seclabel",
	"nnp_nosuid_transition",
	"genfs_seclabel_symlinks",
	"ioctl_skip_cloexec",
	"userspace_initial_context",
};
/* clang-format on */

#endif /* _SEMIKUX_POLICYCAP_NAMES_H_ */
