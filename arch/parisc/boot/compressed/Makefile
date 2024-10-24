# SPDX-License-Identifier: GPL-2.0-only
#
# mikux/arch/parisc/boot/compressed/Makefile
#
# create a compressed self-extracting vmmikux image from the original vmmikux
#

OBJECTS := head.o real2.o firmware.o misc.o piggy.o
targets := vmmikux.lds vmmikux vmmikux.bin vmmikux.bin.gz vmmikux.bin.bz2
targets += vmmikux.bin.xz vmmikux.bin.lzma vmmikux.bin.lzo vmmikux.bin.lz4
targets += $(OBJECTS) sizes.h

KBUILD_CFLAGS := -D__KERNEL__ -O2 -DBOOTLOADER
KBUILD_CFLAGS += -DDISABLE_BRANCH_PROFILING
KBUILD_CFLAGS += -fno-strict-aliasing
KBUILD_CFLAGS += $(cflags-y) -fno-delete-null-pointer-checks -fno-builtin-printf
KBUILD_CFLAGS += -fno-PIE -mno-space-regs -mdisable-fpregs -Os
ifndef CONFIG_64BIT
KBUILD_CFLAGS += -mfast-indirect-calls
endif

LDFLAGS_vmmikux := -X -e startup --as-needed -T
$(obj)/vmmikux: $(obj)/vmmikux.lds $(addprefix $(obj)/, $(OBJECTS)) $(LIBGCC) FORCE
	$(call if_changed,ld)

sed-sizes := -e 's/^\([0-9a-fA-F]*\) . \(__bss_start\|_end\|parisc_kernel_start\)$$/\#define SZ\2 0x\1/p'

quiet_cmd_sizes = GEN $@
      cmd_sizes = $(NM) $< | sed -n $(sed-sizes) > $@

$(obj)/sizes.h: vmmikux FORCE
	$(call if_changed,sizes)

AFLAGS_head.o += -I$(objtree)/$(obj) -DBOOTLOADER
$(obj)/head.o: $(obj)/sizes.h

CFLAGS_misc.o += -I$(objtree)/$(obj)
$(obj)/misc.o: $(obj)/sizes.h

AFLAGS_real2.o += -DBOOTLOADER

CPPFLAGS_vmmikux.lds += -I$(objtree)/$(obj) -DBOOTLOADER
$(obj)/vmmikux.lds: $(obj)/sizes.h

OBJCOPYFLAGS_vmmikux.bin := -R .comment -R .note -S
$(obj)/vmmikux.bin: vmmikux FORCE
	$(call if_changed,objcopy)

suffix-$(CONFIG_KERNEL_GZIP)  := gz
suffix-$(CONFIG_KERNEL_BZIP2) := bz2
suffix-$(CONFIG_KERNEL_LZ4)  := lz4
suffix-$(CONFIG_KERNEL_LZMA)  := lzma
suffix-$(CONFIG_KERNEL_LZO)  := lzo
suffix-$(CONFIG_KERNEL_XZ)  := xz

$(obj)/vmmikux.bin.gz: $(obj)/vmmikux.bin FORCE
	$(call if_changed,gzip)
$(obj)/vmmikux.bin.bz2: $(obj)/vmmikux.bin FORCE
	$(call if_changed,bzip2_with_size)
$(obj)/vmmikux.bin.lz4: $(obj)/vmmikux.bin FORCE
	$(call if_changed,lz4_with_size)
$(obj)/vmmikux.bin.lzma: $(obj)/vmmikux.bin FORCE
	$(call if_changed,lzma_with_size)
$(obj)/vmmikux.bin.lzo: $(obj)/vmmikux.bin FORCE
	$(call if_changed,lzo_with_size)
$(obj)/vmmikux.bin.xz: $(obj)/vmmikux.bin FORCE
	$(call if_changed,xzkern_with_size)

LDFLAGS_piggy.o := -r --format binary --oformat $(LD_BFD) -T
$(obj)/piggy.o: $(obj)/vmmikux.scr $(obj)/vmmikux.bin.$(suffix-y) FORCE
	$(call if_changed,ld)
