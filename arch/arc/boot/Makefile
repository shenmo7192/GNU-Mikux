# SPDX-License-Identifier: GPL-2.0

# uImage build relies on mkimage being available on your host for ARC target
# You will need to build u-boot for ARC, rename mkimage to arc-elf32-mkimage
# and make sure it's reachable from your PATH

OBJCOPYFLAGS= -O binary -R .note -R .note.gnu.build-id -R .comment -S

MIKUX_START_TEXT = $$($(READELF) -h vmmikux | \
			grep "Entry point address" | grep -o 0x.*)

UIMAGE_LOADADDR    = $(CONFIG_MIKUX_LINK_BASE)
UIMAGE_ENTRYADDR   = $(MIKUX_START_TEXT)

targets += vmmikux.bin
targets += vmmikux.bin.gz
targets += vmmikux.bin.lzma
targets += uImage.bin
targets += uImage.gz
targets += uImage.lzma

$(obj)/vmmikux.bin: vmmikux FORCE
	$(call if_changed,objcopy)

$(obj)/vmmikux.bin.gz: $(obj)/vmmikux.bin FORCE
	$(call if_changed,gzip)

$(obj)/vmmikux.bin.lzma: $(obj)/vmmikux.bin FORCE
	$(call if_changed,lzma)

$(obj)/uImage.bin: $(obj)/vmmikux.bin FORCE
	$(call if_changed,uimage,none)

$(obj)/uImage.gz: $(obj)/vmmikux.bin.gz FORCE
	$(call if_changed,uimage,gzip)

$(obj)/uImage.lzma: $(obj)/vmmikux.bin.lzma FORCE
	$(call if_changed,uimage,lzma)
