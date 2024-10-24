# SPDX-License-Identifier: GPL-2.0
#
# mikux/arch/sh/boot/compressed/Makefile
#
# create a compressed vmmikux image from the original vmmikux
#

OBJECTS := head_32.o misc.o piggy.o \
           ashiftrt.o ashldi3.o ashrsi3.o ashlsi3.o lshrsi3.o

targets := vmmikux vmmikux.bin vmmikux.bin.gz vmmikux.bin.bz2 \
           vmmikux.bin.lzma vmmikux.bin.xz vmmikux.bin.lzo $(OBJECTS)

#
# IMAGE_OFFSET is the load offset of the compression loader
#
ifeq ($(CONFIG_32BIT),y)
IMAGE_OFFSET	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_MEMORY_START)  + \
			$(CONFIG_BOOT_LINK_OFFSET)]')
else
IMAGE_OFFSET	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_PAGE_OFFSET)  + \
			$(KERNEL_MEMORY) + \
			$(CONFIG_BOOT_LINK_OFFSET)]')
endif

ccflags-remove-$(CONFIG_MCOUNT) += -pg

LDFLAGS_vmmikux := --oformat $(ld-bfd) -Ttext $(IMAGE_OFFSET) -e startup \
		   -T $(obj)/../../kernel/vmmikux.lds

KBUILD_CFLAGS += -DDISABLE_BRANCH_PROFILING

$(obj)/vmmikux: $(addprefix $(obj)/, $(OBJECTS)) FORCE
	$(call if_changed,ld)

$(obj)/vmmikux.bin: vmmikux FORCE
	$(call if_changed,objcopy)

$(obj)/vmmikux.bin.gz: $(obj)/vmmikux.bin FORCE
	$(call if_changed,gzip)
$(obj)/vmmikux.bin.bz2: $(obj)/vmmikux.bin FORCE
	$(call if_changed,bzip2_with_size)
$(obj)/vmmikux.bin.lzma: $(obj)/vmmikux.bin FORCE
	$(call if_changed,lzma_with_size)
$(obj)/vmmikux.bin.xz: $(obj)/vmmikux.bin FORCE
	$(call if_changed,xzkern_with_size)
$(obj)/vmmikux.bin.lzo: $(obj)/vmmikux.bin FORCE
	$(call if_changed,lzo_with_size)

OBJCOPYFLAGS += -R .empty_zero_page

LDFLAGS_piggy.o := -r --format binary --oformat $(ld-bfd) -T

$(obj)/piggy.o: $(obj)/vmmikux.scr $(obj)/vmmikux.bin.$(suffix_y) FORCE
	$(call if_changed,ld)
