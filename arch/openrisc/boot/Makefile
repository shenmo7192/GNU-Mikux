# SPDX-License-Identifier: GPL-2.0
#
# Makefile for bootable kernel images
#

targets += vmmikux.bin

OBJCOPYFLAGS_vmmikux.bin := -O binary
$(obj)/vmmikux.bin: vmmikux FORCE
	$(call if_changed,objcopy)
