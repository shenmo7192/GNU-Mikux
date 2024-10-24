#
# arch/nios2/boot/Makefile
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

UIMAGE_LOADADDR = $(shell $(NM) vmmikux | awk '$$NF == "_stext" {print $$1}')
UIMAGE_ENTRYADDR = $(shell $(NM) vmmikux | awk '$$NF == "_start" {print $$1}')
UIMAGE_COMPRESSION = gzip

OBJCOPYFLAGS_vmmikux.bin := -O binary

targets += vmmikux.bin vmmikux.gz vmImage

$(obj)/vmmikux.bin: vmmikux FORCE
	$(call if_changed,objcopy)

$(obj)/vmmikux.gz: $(obj)/vmmikux.bin FORCE
	$(call if_changed,gzip)

$(obj)/vmImage: $(obj)/vmmikux.gz FORCE
	$(call if_changed,uimage)
	@$(kecho) 'Kernel: $@ is ready'

$(obj)/zImage: $(obj)/compressed/vmmikux FORCE
	$(call if_changed,objcopy)
	@$(kecho) 'Kernel: $@ is ready'

$(obj)/compressed/vmmikux: $(obj)/vmmikux.gz FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@
