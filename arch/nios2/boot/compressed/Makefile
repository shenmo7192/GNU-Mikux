# SPDX-License-Identifier: GPL-2.0
#
# create a compressed vmmikux image from the original vmmikux
#

targets		:= vmmikux head.o misc.o piggy.o vmmikux.lds
asflags-y	:=

OBJECTS = $(obj)/head.o $(obj)/misc.o

LDFLAGS_vmmikux := -T

$(obj)/vmmikux: $(obj)/vmmikux.lds $(OBJECTS) $(obj)/piggy.o FORCE
	$(call if_changed,ld)

LDFLAGS_piggy.o := -r --format binary --oformat elf32-littlenios2 -T

$(obj)/piggy.o: $(obj)/vmmikux.scr $(obj)/../vmmikux.gz FORCE
	$(call if_changed,ld)
