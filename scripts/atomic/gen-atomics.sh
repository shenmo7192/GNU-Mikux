#!/bin/sh
# SPDX-License-Identifier: GPL-2.0
#
# Generate atomic headers

ATOMICDIR=$(dirname $0)
ATOMICTBL=${ATOMICDIR}/atomics.tbl
MIKUXDIR=${ATOMICDIR}/../..

cat <<EOF |
gen-atomic-instrumented.sh      mikux/atomic/atomic-instrumented.h
gen-atomic-long.sh              mikux/atomic/atomic-long.h
gen-atomic-fallback.sh          mikux/atomic/atomic-arch-fallback.h
EOF
while read script header args; do
	/bin/sh ${ATOMICDIR}/${script} ${ATOMICTBL} ${args} > ${MIKUXDIR}/include/${header}
	HASH="$(sha1sum ${MIKUXDIR}/include/${header})"
	HASH="${HASH%% *}"
	printf "// %s\n" "${HASH}" >> ${MIKUXDIR}/include/${header}
done
