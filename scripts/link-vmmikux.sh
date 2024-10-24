#!/bin/sh
# SPDX-License-Identifier: GPL-2.0
#
# link vmmikux
#
# vmmikux is linked from the objects in vmmikux.a and $(KBUILD_VMMIKUX_LIBS).
# vmmikux.a contains objects that are linked unconditionally.
# $(KBUILD_VMMIKUX_LIBS) are archives which are linked conditionally
# (not within --whole-archive), and do not require symbol indexes added.
#
# vmmikux
#   ^
#   |
#   +--< vmmikux.a
#   |
#   +--< $(KBUILD_VMMIKUX_LIBS)
#   |    +--< lib/lib.a + more
#   |
#   +-< ${kallsymso} (see description in KALLSYMS section)
#
# vmmikux version (uname -v) cannot be updated during normal
# descending-into-subdirs phase since we do not yet know if we need to
# update vmmikux.
# Therefore this step is delayed until just before final link of vmmikux.
#
# System.map is generated to document addresses of all kernel symbols

# Error out on error
set -e

LD="$1"
KBUILD_LDFLAGS="$2"
LDFLAGS_vmmikux="$3"

is_enabled() {
	grep -q "^$1=y" include/config/auto.conf
}

# Nice output in kbuild format
# Will be supressed by "make -s"
info()
{
	printf "  %-7s %s\n" "${1}" "${2}"
}

# Link of vmmikux
# ${1} - output file
vmmikux_link()
{
	local output=${1}
	local objs
	local libs
	local ld
	local ldflags
	local ldlibs

	info LD ${output}

	# skip output file argument
	shift

	if is_enabled CONFIG_LTO_CLANG || is_enabled CONFIG_X86_KERNEL_IBT; then
		# Use vmmikux.o instead of performing the slow LTO link again.
		objs=vmmikux.o
		libs=
	else
		objs=vmmikux.a
		libs="${KBUILD_VMMIKUX_LIBS}"
	fi

	if is_enabled CONFIG_MODULES; then
		objs="${objs} .vmmikux.export.o"
	fi

	objs="${objs} init/version-timestamp.o"

	if [ "${SRCARCH}" = "um" ]; then
		wl=-Wl,
		ld="${CC}"
		ldflags="${CFLAGS_vmmikux}"
		ldlibs="-lutil -lrt -lpthread"
	else
		wl=
		ld="${LD}"
		ldflags="${KBUILD_LDFLAGS} ${LDFLAGS_vmmikux}"
		ldlibs=
	fi

	ldflags="${ldflags} ${wl}--script=${objtree}/${KBUILD_LDS}"

	# The kallsyms linking does not need debug symbols included.
	if [ -n "${strip_debug}" ] ; then
		ldflags="${ldflags} ${wl}--strip-debug"
	fi

	if is_enabled CONFIG_VMMIKUX_MAP; then
		ldflags="${ldflags} ${wl}-Map=${output}.map"
	fi

	${ld} ${ldflags} -o ${output}					\
		${wl}--whole-archive ${objs} ${wl}--no-whole-archive	\
		${wl}--start-group ${libs} ${wl}--end-group		\
		${kallsymso} ${btf_vmmikux_bin_o} ${ldlibs}
}

# generate .BTF typeinfo from DWARF debuginfo
# ${1} - vmmikux image
gen_btf()
{
	local btf_data=${1}.btf.o

	info BTF "${btf_data}"
	LLVM_OBJCOPY="${OBJCOPY}" ${PAHOLE} -J ${PAHOLE_FLAGS} ${1}

	# Create ${btf_data} which contains just .BTF section but no symbols. Add
	# SHF_ALLOC because .BTF will be part of the vmmikux image. --strip-all
	# deletes all symbols including __start_BTF and __stop_BTF, which will
	# be redefined in the linker script. Add 2>/dev/null to suppress GNU
	# objcopy warnings: "empty loadable segment detected at ..."
	${OBJCOPY} --only-section=.BTF --set-section-flags .BTF=alloc,readonly \
		--strip-all ${1} "${btf_data}" 2>/dev/null
	# Change e_type to ET_REL so that it can be used to link final vmmikux.
	# GNU ld 2.35+ and lld do not allow an ET_EXEC input.
	if is_enabled CONFIG_CPU_BIG_ENDIAN; then
		et_rel='\0\1'
	else
		et_rel='\1\0'
	fi
	printf "${et_rel}" | dd of="${btf_data}" conv=notrunc bs=1 seek=16 status=none

	btf_vmmikux_bin_o=${btf_data}
}

# Create ${2}.o file with all symbols from the ${1} object file
kallsyms()
{
	local kallsymopt;

	if is_enabled CONFIG_KALLSYMS_ALL; then
		kallsymopt="${kallsymopt} --all-symbols"
	fi

	if is_enabled CONFIG_KALLSYMS_ABSOLUTE_PERCPU; then
		kallsymopt="${kallsymopt} --absolute-percpu"
	fi

	info KSYMS "${2}.S"
	scripts/kallsyms ${kallsymopt} "${1}" > "${2}.S"

	info AS "${2}.o"
	${CC} ${NOSTDINC_FLAGS} ${MIKUXINCLUDE} ${KBUILD_CPPFLAGS} \
	      ${KBUILD_AFLAGS} ${KBUILD_AFLAGS_KERNEL} -c -o "${2}.o" "${2}.S"

	kallsymso=${2}.o
}

# Perform kallsyms for the given temporary vmmikux.
sysmap_and_kallsyms()
{
	mksysmap "${1}" "${1}.syms"
	kallsyms "${1}.syms" "${1}.kallsyms"

	kallsyms_sysmap=${1}.syms
}

# Create map file with all symbols from ${1}
# See mksymap for additional details
mksysmap()
{
	info NM ${2}
	${NM} -n "${1}" | sed -f "${srctree}/scripts/mksysmap" > "${2}"
}

sorttable()
{
	${objtree}/scripts/sorttable ${1}
}

cleanup()
{
	rm -f .btf.*
	rm -f System.map
	rm -f vmmikux
	rm -f vmmikux.map
}

# Use "make V=1" to debug this script
case "${KBUILD_VERBOSE}" in
*1*)
	set -x
	;;
esac

if [ "$1" = "clean" ]; then
	cleanup
	exit 0
fi

${MAKE} -f "${srctree}/scripts/Makefile.build" obj=init init/version-timestamp.o

btf_vmmikux_bin_o=
kallsymso=
strip_debug=

if is_enabled CONFIG_KALLSYMS; then
	true > .tmp_vmmikux.kallsyms0.syms
	kallsyms .tmp_vmmikux.kallsyms0.syms .tmp_vmmikux0.kallsyms
fi

if is_enabled CONFIG_KALLSYMS || is_enabled CONFIG_DEBUG_INFO_BTF; then

	# The kallsyms linking does not need debug symbols, but the BTF does.
	if ! is_enabled CONFIG_DEBUG_INFO_BTF; then
		strip_debug=1
	fi

	vmmikux_link .tmp_vmmikux1
fi

if is_enabled CONFIG_DEBUG_INFO_BTF; then
	if ! gen_btf .tmp_vmmikux1; then
		echo >&2 "Failed to generate BTF for vmmikux"
		echo >&2 "Try to disable CONFIG_DEBUG_INFO_BTF"
		exit 1
	fi
fi

if is_enabled CONFIG_KALLSYMS; then

	# kallsyms support
	# Generate section listing all symbols and add it into vmmikux
	# It's a four step process:
	# 0)  Generate a dummy __kallsyms with empty symbol list.
	# 1)  Link .tmp_vmmikux.kallsyms1 so it has all symbols and sections,
	#     with a dummy __kallsyms.
	#     Running kallsyms on that gives us .tmp_kallsyms1.o with
	#     the right size
	# 2)  Link .tmp_vmmikux.kallsyms2 so it now has a __kallsyms section of
	#     the right size, but due to the added section, some
	#     addresses have shifted.
	#     From here, we generate a correct .tmp_vmmikux.kallsyms2.o
	# 3)  That link may have expanded the kernel image enough that
	#     more linker branch stubs / trampolines had to be added, which
	#     introduces new names, which further expands kallsyms. Do another
	#     pass if that is the case. In theory it's possible this results
	#     in even more stubs, but unlikely.
	#     KALLSYMS_EXTRA_PASS=1 may also used to debug or work around
	#     other bugs.
	# 4)  The correct ${kallsymso} is linked into the final vmmikux.
	#
	# a)  Verify that the System.map from vmmikux matches the map from
	#     ${kallsymso}.

	# The kallsyms linking does not need debug symbols included.
	strip_debug=1

	sysmap_and_kallsyms .tmp_vmmikux1
	size1=$(${CONFIG_SHELL} "${srctree}/scripts/file-size.sh" ${kallsymso})

	vmmikux_link .tmp_vmmikux2
	sysmap_and_kallsyms .tmp_vmmikux2
	size2=$(${CONFIG_SHELL} "${srctree}/scripts/file-size.sh" ${kallsymso})

	if [ $size1 -ne $size2 ] || [ -n "${KALLSYMS_EXTRA_PASS}" ]; then
		vmmikux_link .tmp_vmmikux3
		sysmap_and_kallsyms .tmp_vmmikux3
	fi
fi

strip_debug=

vmmikux_link vmmikux

# fill in BTF IDs
if is_enabled CONFIG_DEBUG_INFO_BTF; then
	info BTFIDS vmmikux
	${RESOLVE_BTFIDS} vmmikux
fi

mksysmap vmmikux System.map

if is_enabled CONFIG_BUILDTIME_TABLE_SORT; then
	info SORTTAB vmmikux
	if ! sorttable vmmikux; then
		echo >&2 Failed to sort kernel tables
		exit 1
	fi
fi

# step a (see comment above)
if is_enabled CONFIG_KALLSYMS; then
	if ! cmp -s System.map "${kallsyms_sysmap}"; then
		echo >&2 Inconsistent kallsyms data
		echo >&2 'Try "make KALLSYMS_EXTRA_PASS=1" as a workaround'
		exit 1
	fi
fi

# For fixdep
echo "vmmikux: $0" > .vmmikux.d
