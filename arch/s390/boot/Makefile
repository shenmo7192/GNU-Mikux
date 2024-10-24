# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the mikux s390-specific parts of the memory manager.
#

# Tooling runtimes are unavailable and cannot be linked for early boot code
KCOV_INSTRUMENT := n
GCOV_PROFILE := n
UBSAN_SANITIZE := n
KASAN_SANITIZE := n
KCSAN_SANITIZE := n
KMSAN_SANITIZE := n

#
# Use minimum architecture level so it is possible to print an error
# message if the kernel is started on a machine which is too old
#
CC_FLAGS_MARCH_MINIMUM := -march=z10

KBUILD_AFLAGS := $(filter-out $(CC_FLAGS_MARCH),$(KBUILD_AFLAGS_DECOMPRESSOR))
KBUILD_CFLAGS := $(filter-out $(CC_FLAGS_MARCH),$(KBUILD_CFLAGS_DECOMPRESSOR))
KBUILD_AFLAGS += $(CC_FLAGS_MARCH_MINIMUM)
KBUILD_CFLAGS += $(CC_FLAGS_MARCH_MINIMUM)

CFLAGS_sclp_early_core.o += -I$(srctree)/drivers/s390/char

obj-y	:= head.o als.o startup.o physmem_info.o ipl_parm.o ipl_report.o vmem.o
obj-y	+= string.o ebcdic.o sclp_early_core.o mem.o ipl_vmparm.o cmdline.o
obj-y	+= version.o pgm_check_info.o ctype.o ipl_data.o relocs.o alternative.o
obj-y	+= uv.o printk.o
obj-$(CONFIG_RANDOMIZE_BASE)	+= kaslr.o
obj-y	+= $(if $(CONFIG_KERNEL_UNCOMPRESSED),,decompressor.o) info.o
obj-$(CONFIG_KERNEL_ZSTD) += clz_ctz.o
obj-$(CONFIG_KMSAN) += kmsan.o
obj-all := $(obj-y) piggy.o syms.o

targets	:= bzImage section_cmp.boot.data section_cmp.boot.preserved.data $(obj-y)
targets	+= vmmikux.lds vmmikux vmmikux.bin vmmikux.bin.gz vmmikux.bin.bz2
targets += vmmikux.bin.xz vmmikux.bin.lzma vmmikux.bin.lzo vmmikux.bin.lz4
targets += vmmikux.bin.zst info.bin syms.bin vmmikux.syms $(obj-all)
targets += relocs.S

OBJECTS := $(addprefix $(obj)/,$(obj-y))
OBJECTS_ALL := $(addprefix $(obj)/,$(obj-all))

clean-files += vmmikux.map

quiet_cmd_section_cmp = SECTCMP $*
define cmd_section_cmp
	s1=`$(OBJDUMP) -t "$<" | grep "\s$*\s\+" | sort | \
		sed -n "/0000000000000000/! s/.*\s$*\s\+//p" | sha256sum`; \
	s2=`$(OBJDUMP) -t "$(word 2,$^)" | grep "\s$*\s\+" | sort | \
		sed -n "/0000000000000000/! s/.*\s$*\s\+//p" | sha256sum`; \
	if [ "$$s1" != "$$s2" ]; then \
		echo "error: section $* differs between $< and $(word 2,$^)" >&2; \
		exit 1; \
	fi; \
	touch $@
endef

$(obj)/bzImage: $(obj)/vmmikux $(obj)/section_cmp.boot.data $(obj)/section_cmp.boot.preserved.data FORCE
	$(call if_changed,objcopy)

$(obj)/section_cmp%: vmmikux $(obj)/vmmikux FORCE
	$(call if_changed,section_cmp)

LDFLAGS_vmmikux-$(CONFIG_LD_ORPHAN_WARN) := --orphan-handling=$(CONFIG_LD_ORPHAN_WARN_LEVEL)
LDFLAGS_vmmikux := $(LDFLAGS_vmmikux-y) --oformat $(LD_BFD) -e startup $(if $(CONFIG_VMMIKUX_MAP),-Map=$(obj)/vmmikux.map) --build-id=sha1 -T
$(obj)/vmmikux: $(obj)/vmmikux.lds $(OBJECTS_ALL) FORCE
	$(call if_changed,ld)

LDFLAGS_vmmikux.syms := $(LDFLAGS_vmmikux-y) --oformat $(LD_BFD) -e startup -T
$(obj)/vmmikux.syms: $(obj)/vmmikux.lds $(OBJECTS) FORCE
	$(call if_changed,ld)

quiet_cmd_dumpsyms = DUMPSYMS $<
define cmd_dumpsyms
	$(NM) -n -S --format=bsd "$<" | sed -nE 's/^0*([0-9a-fA-F]+) 0*([0-9a-fA-F]+) [tT] ([^ ]*)$$/\1 \2 \3/p' | tr '\n' '\0' > "$@"
endef

$(obj)/syms.bin: $(obj)/vmmikux.syms FORCE
	$(call if_changed,dumpsyms)

OBJCOPYFLAGS_syms.o := -I binary -O elf64-s390 -B s390:64-bit --rename-section .data=.decompressor.syms
$(obj)/syms.o: $(obj)/syms.bin FORCE
	$(call if_changed,objcopy)

OBJCOPYFLAGS_info.bin := -O binary --only-section=.vmmikux.info --set-section-flags .vmmikux.info=alloc,load
$(obj)/info.bin: vmmikux FORCE
	$(call if_changed,objcopy)

OBJCOPYFLAGS_info.o := -I binary -O elf64-s390 -B s390:64-bit --rename-section .data=.vmmikux.info
$(obj)/info.o: $(obj)/info.bin FORCE
	$(call if_changed,objcopy)

OBJCOPYFLAGS_vmmikux.bin := -O binary --remove-section=.comment --remove-section=.vmmikux.info -S
$(obj)/vmmikux.bin: vmmikux FORCE
	$(call if_changed,objcopy)

# relocs.S is created by the vmmikux postlink step.
$(obj)/relocs.S: vmmikux
	@true

suffix-$(CONFIG_KERNEL_GZIP)  := .gz
suffix-$(CONFIG_KERNEL_BZIP2) := .bz2
suffix-$(CONFIG_KERNEL_LZ4)  := .lz4
suffix-$(CONFIG_KERNEL_LZMA)  := .lzma
suffix-$(CONFIG_KERNEL_LZO)  := .lzo
suffix-$(CONFIG_KERNEL_XZ)  := .xz
suffix-$(CONFIG_KERNEL_ZSTD)  := .zst

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
$(obj)/vmmikux.bin.zst: $(obj)/vmmikux.bin FORCE
	$(call if_changed,zstd22_with_size)

OBJCOPYFLAGS_piggy.o := -I binary -O elf64-s390 -B s390:64-bit --rename-section .data=.vmmikux.bin.compressed
$(obj)/piggy.o: $(obj)/vmmikux.bin$(suffix-y) FORCE
	$(call if_changed,objcopy)
