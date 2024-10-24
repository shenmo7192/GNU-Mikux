#!/bin/sh
# SPDX-License-Identifier: LGPL-2.1

if [ $# -ne 1 ] ; then
	beauty_uapi_mikux_dir=tools/perf/trace/beauty/include/uapi/mikux/
else
	beauty_uapi_mikux_dir=$1
fi

mikux_mount=${beauty_uapi_mikux_dir}/mount.h

printf "static const char *fsconfig_cmds[] = {\n"
ms='[[:space:]]*'
sed -nr "s/^${ms}FSCONFIG_([[:alnum:]_]+)${ms}=${ms}([[:digit:]]+)${ms},.*/\t[\2] = \"\1\",/p" \
	${mikux_mount}
printf "};\n"
