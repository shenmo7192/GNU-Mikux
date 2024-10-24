#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 1995, 1998, 2001, 2002 by Ralf Baechle
# Copyright (C) 2004  Maciej W. Rozycki
#

#
# Some DECstations need all possible sections of an ECOFF executable
#
ifdef CONFIG_MACH_DECSTATION
  e2eflag := -a
endif

#
# Drop some uninteresting sections in the kernel.
# This is only relevant for ELF kernels but doesn't hurt a.out
#
drop-sections := .reginfo .mdebug .comment .note .pdr .options .MIPS.options
strip-flags   := $(addprefix --remove-section=,$(drop-sections))

hostprogs := elf2ecoff

suffix-y			:= bin
suffix-$(CONFIG_KERNEL_BZIP2)	:= bz2
suffix-$(CONFIG_KERNEL_GZIP)	:= gz
suffix-$(CONFIG_KERNEL_LZMA)	:= lzma
suffix-$(CONFIG_KERNEL_LZO)	:= lzo

targets := vmmikux.ecoff
quiet_cmd_ecoff = ECOFF	  $@
      cmd_ecoff = $(obj)/elf2ecoff $(VMMIKUX) $@ $(e2eflag)
$(obj)/vmmikux.ecoff: $(obj)/elf2ecoff $(VMMIKUX) FORCE
	$(call if_changed,ecoff)

targets += vmmikux.bin
quiet_cmd_bin = OBJCOPY $@
      cmd_bin = $(OBJCOPY) -O binary $(strip-flags) $(VMMIKUX) $@
$(obj)/vmmikux.bin: $(VMMIKUX) FORCE
	$(call if_changed,bin)

targets += vmmikux.srec
quiet_cmd_srec = OBJCOPY $@
      cmd_srec = $(OBJCOPY) -S -O srec $(strip-flags) $(VMMIKUX) $@
$(obj)/vmmikux.srec: $(VMMIKUX) FORCE
	$(call if_changed,srec)

UIMAGE_LOADADDR  = $(VMMIKUX_LOAD_ADDRESS)
UIMAGE_ENTRYADDR = $(VMMIKUX_ENTRY_ADDRESS)

#
# Compressed vmmikux images
#

extra-y += vmmikux.bin.bz2
extra-y += vmmikux.bin.gz
extra-y += vmmikux.bin.lzma
extra-y += vmmikux.bin.lzo

$(obj)/vmmikux.bin.bz2: $(obj)/vmmikux.bin FORCE
	$(call if_changed,bzip2)

$(obj)/vmmikux.bin.gz: $(obj)/vmmikux.bin FORCE
	$(call if_changed,gzip)

$(obj)/vmmikux.bin.lzma: $(obj)/vmmikux.bin FORCE
	$(call if_changed,lzma)

$(obj)/vmmikux.bin.lzo: $(obj)/vmmikux.bin FORCE
	$(call if_changed,lzo)

#
# Compressed u-boot images
#

targets += uImage
targets += uImage.bin
targets += uImage.bz2
targets += uImage.gz
targets += uImage.lzma
targets += uImage.lzo

$(obj)/uImage.bin: $(obj)/vmmikux.bin FORCE
	$(call if_changed,uimage,none)

$(obj)/uImage.bz2: $(obj)/vmmikux.bin.bz2 FORCE
	$(call if_changed,uimage,bzip2)

$(obj)/uImage.gz: $(obj)/vmmikux.bin.gz FORCE
	$(call if_changed,uimage,gzip)

$(obj)/uImage.lzma: $(obj)/vmmikux.bin.lzma FORCE
	$(call if_changed,uimage,lzma)

$(obj)/uImage.lzo: $(obj)/vmmikux.bin.lzo FORCE
	$(call if_changed,uimage,lzo)

$(obj)/uImage: $(obj)/uImage.$(suffix-y)
	@ln -sf $(notdir $<) $@
	@echo '  Image $@ is ready'

#
# Flattened Image Tree (.itb) images
#

ifeq ($(ADDR_BITS),32)
itb_addr_cells = 1
endif
ifeq ($(ADDR_BITS),64)
itb_addr_cells = 2
endif

targets += vmmikux.its.S

quiet_cmd_its_cat = CAT     $@
      cmd_its_cat = cat $(real-prereqs) >$@

$(obj)/vmmikux.its.S: $(addprefix $(srctree)/arch/mips/$(PLATFORM)/,$(ITS_INPUTS)) FORCE
	$(call if_changed,its_cat)

targets += vmmikux.its
targets += vmmikux.gz.its
targets += vmmikux.bz2.its
targets += vmmikux.lzma.its
targets += vmmikux.lzo.its

quiet_cmd_cpp_its_S = ITS     $@
      cmd_cpp_its_S = $(CPP) -P -C -o $@ $< \
		        -DKERNEL_NAME="\"Mikux $(KERNELRELEASE)\"" \
			-DVMMIKUX_BINARY="\"$(3)\"" \
			-DVMMIKUX_COMPRESSION="\"$(2)\"" \
			-DVMMIKUX_LOAD_ADDRESS=$(VMMIKUX_LOAD_ADDRESS) \
			-DVMMIKUX_ENTRY_ADDRESS=$(VMMIKUX_ENTRY_ADDRESS) \
			-DADDR_BITS=$(ADDR_BITS) \
			-DADDR_CELLS=$(itb_addr_cells)

$(obj)/vmmikux.its: $(obj)/vmmikux.its.S $(VMMIKUX) FORCE
	$(call if_changed,cpp_its_S,none,vmmikux.bin)

$(obj)/vmmikux.gz.its: $(obj)/vmmikux.its.S $(VMMIKUX) FORCE
	$(call if_changed,cpp_its_S,gzip,vmmikux.bin.gz)

$(obj)/vmmikux.bz2.its: $(obj)/vmmikux.its.S $(VMMIKUX)  FORCE
	$(call if_changed,cpp_its_S,bzip2,vmmikux.bin.bz2)

$(obj)/vmmikux.lzma.its: $(obj)/vmmikux.its.S $(VMMIKUX) FORCE
	$(call if_changed,cpp_its_S,lzma,vmmikux.bin.lzma)

$(obj)/vmmikux.lzo.its: $(obj)/vmmikux.its.S $(VMMIKUX) FORCE
	$(call if_changed,cpp_its_S,lzo,vmmikux.bin.lzo)

targets += vmmikux.itb
targets += vmmikux.gz.itb
targets += vmmikux.bz2.itb
targets += vmmikux.lzma.itb
targets += vmmikux.lzo.itb

quiet_cmd_itb-image = ITB     $@
      cmd_itb-image = \
		env PATH="$(objtree)/scripts/dtc:$(PATH)" \
		$(BASH) $(MKIMAGE) \
		-D "-I dts -O dtb -p 500 \
			--include $(objtree)/arch/mips \
			--warning no-unit_address_vs_reg" \
		-f $(2) $@

$(obj)/vmmikux.itb: $(obj)/vmmikux.its $(obj)/vmmikux.bin FORCE
	$(call if_changed,itb-image,$<)

$(obj)/vmmikux.%.itb: $(obj)/vmmikux.%.its $(obj)/vmmikux.bin.% FORCE
	$(call if_changed,itb-image,$<)

# for cleaning
subdir- += compressed tools
