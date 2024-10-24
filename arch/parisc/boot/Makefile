# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile for the mikux parisc-specific parts of the boot image creator.
#

targets := image
targets += bzImage
subdir- := compressed

$(obj)/image: vmmikux FORCE
	$(call if_changed,objcopy)

$(obj)/bzImage: $(if $(CONFIG_KERNEL_UNCOMPRESSED),$(objtree)/vmmikux,$(obj)/compressed/vmmikux) FORCE
	$(call if_changed,objcopy)

$(obj)/compressed/vmmikux: FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@
