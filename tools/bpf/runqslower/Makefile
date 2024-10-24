# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
include ../../scripts/Makefile.include

OUTPUT ?= $(abspath .output)/

BPFTOOL_OUTPUT := $(OUTPUT)bpftool/
DEFAULT_BPFTOOL := $(BPFTOOL_OUTPUT)bootstrap/bpftool
BPFTOOL ?= $(DEFAULT_BPFTOOL)
LIBBPF_SRC := $(abspath ../../lib/bpf)
BPFOBJ_OUTPUT := $(OUTPUT)libbpf/
BPFOBJ := $(BPFOBJ_OUTPUT)libbpf.a
BPF_DESTDIR := $(BPFOBJ_OUTPUT)
BPF_INCLUDE := $(BPF_DESTDIR)/include
INCLUDES := -I$(OUTPUT) -I$(BPF_INCLUDE) -I$(abspath ../../include/uapi)
CFLAGS := -g -Wall $(CLANG_CROSS_FLAGS)
CFLAGS += $(EXTRA_CFLAGS)
LDFLAGS += $(EXTRA_LDFLAGS)
LDLIBS += -lelf -lz

# Try to detect best kernel BTF source
KERNEL_REL := $(shell uname -r)
VMMIKUX_BTF_PATHS := $(if $(O),$(O)/vmmikux)		\
	$(if $(KBUILD_OUTPUT),$(KBUILD_OUTPUT)/vmmikux) \
	../../../vmmikux /sys/kernel/btf/vmmikux	\
	/boot/vmmikux-$(KERNEL_REL)
VMMIKUX_BTF_PATH := $(or $(VMMIKUX_BTF),$(firstword			       \
					  $(wildcard $(VMMIKUX_BTF_PATHS))))

ifeq ($(V),1)
Q =
else
Q = @
MAKEFLAGS += --no-print-directory
submake_extras := feature_display=0
endif

.DELETE_ON_ERROR:

.PHONY: all clean runqslower libbpf_hdrs
all: runqslower

runqslower: $(OUTPUT)/runqslower

clean:
	$(call QUIET_CLEAN, runqslower)
	$(Q)$(RM) -r $(BPFOBJ_OUTPUT) $(BPFTOOL_OUTPUT)
	$(Q)$(RM) $(OUTPUT)*.o $(OUTPUT)*.d
	$(Q)$(RM) $(OUTPUT)*.skel.h $(OUTPUT)vmmikux.h
	$(Q)$(RM) $(OUTPUT)runqslower
	$(Q)$(RM) -r .output

libbpf_hdrs: $(BPFOBJ)

$(OUTPUT)/runqslower: $(OUTPUT)/runqslower.o $(BPFOBJ)
	$(QUIET_LINK)$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OUTPUT)/runqslower.o: runqslower.h $(OUTPUT)/runqslower.skel.h	      \
			$(OUTPUT)/runqslower.bpf.o | libbpf_hdrs

$(OUTPUT)/runqslower.bpf.o: $(OUTPUT)/vmmikux.h runqslower.h | libbpf_hdrs

$(OUTPUT)/%.skel.h: $(OUTPUT)/%.bpf.o | $(BPFTOOL)
	$(QUIET_GEN)$(BPFTOOL) gen skeleton $< > $@

$(OUTPUT)/%.bpf.o: %.bpf.c $(BPFOBJ) | $(OUTPUT)
	$(QUIET_GEN)$(CLANG) -g -O2 --target=bpf $(INCLUDES)		      \
		 -c $(filter %.c,$^) -o $@ &&				      \
	$(LLVM_STRIP) -g $@

$(OUTPUT)/%.o: %.c | $(OUTPUT)
	$(QUIET_CC)$(CC) $(CFLAGS) $(INCLUDES) -c $(filter %.c,$^) -o $@

$(OUTPUT) $(BPFOBJ_OUTPUT) $(BPFTOOL_OUTPUT):
	$(QUIET_MKDIR)mkdir -p $@

$(OUTPUT)/vmmikux.h: $(VMMIKUX_BTF_PATH) | $(OUTPUT) $(BPFTOOL)
ifeq ($(VMMIKUX_H),)
	$(Q)if [ ! -e "$(VMMIKUX_BTF_PATH)" ] ; then \
		echo "Couldn't find kernel BTF; set VMMIKUX_BTF to"	       \
			"specify its location." >&2;			       \
		exit 1;\
	fi
	$(QUIET_GEN)$(BPFTOOL) btf dump file $(VMMIKUX_BTF_PATH) format c > $@
else
	$(Q)cp "$(VMMIKUX_H)" $@
endif

$(BPFOBJ): $(wildcard $(LIBBPF_SRC)/*.[ch] $(LIBBPF_SRC)/Makefile) | $(BPFOBJ_OUTPUT)
	$(Q)$(MAKE) $(submake_extras) -C $(LIBBPF_SRC) OUTPUT=$(BPFOBJ_OUTPUT) \
		    DESTDIR=$(BPFOBJ_OUTPUT) prefix= $(abspath $@) install_headers

$(DEFAULT_BPFTOOL): | $(BPFTOOL_OUTPUT)
	$(Q)$(MAKE) $(submake_extras) -C ../bpftool OUTPUT=$(BPFTOOL_OUTPUT) bootstrap
