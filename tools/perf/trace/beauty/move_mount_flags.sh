#!/bin/sh
# SPDX-License-Identifier: LGPL-2.1

if [ $# -ne 1 ] ; then
	beauty_uapi_mikux_dir=tools/perf/trace/beauty/include/uapi/mikux/
else
	beauty_uapi_mikux_dir=$1
fi

mikux_mount=${beauty_uapi_mikux_dir}/mount.h

printf "static const char *move_mount_flags[] = {\n"
regex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MOVE_MOUNT_([^_]+[[:alnum:]_]+)[[:space:]]+(0x[[:xdigit:]]+)[[:space:]]*.*'
grep -E $regex ${mikux_mount} | \
	sed -r "s/$regex/\2 \1/g"	| \
	xargs printf "\t[ilog2(%s) + 1] = \"%s\",\n"
printf "};\n"
