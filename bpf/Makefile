# BPF Makefile

CLANG   ?= clang
BPFTOOL ?= bpftool

ARCH := $(shell uname -m | sed \
          -e 's/x86_64/x86/' \
          -e 's/aarch64/arm64/' \
          -e 's/ppc64le/powerpc/' \
          -e 's/s390x/s390/')

INCLUDES := -I include

CFLAGS := -g -O2 -Wall \
          -target bpf \
          -D__TARGET_ARCH_$(ARCH) \
          $(INCLUDES)

VMLINUX_H := include/vmlinux.h

OUT  := ../build/bpf
SKEL := skel

SRCS  := $(shell find progs -name '*.bpf.c')
OBJS  := $(patsubst progs/%.bpf.c,$(OUT)/%.bpf.o,$(SRCS))
DEPS  := $(OBJS:.bpf.o=.bpf.d)
SKELS := $(patsubst progs/%.bpf.c,$(SKEL)/%.skel.h,$(SRCS))

.PHONY: all clean vmlinux

.SECONDARY: $(OBJS)

all: $(SKELS)

vmlinux: $(VMLINUX_H)

$(VMLINUX_H):
	$(BPFTOOL) btf dump file /sys/kernel/btf/vmlinux format c > $@

$(OBJS): $(OUT)/%.bpf.o: progs/%.bpf.c $(VMLINUX_H)
	@mkdir -p $(dir $@)
	$(CLANG) $(CFLAGS) -MMD -MP -MF $(OUT)/$*.bpf.d -c $< -o $@

$(SKELS): $(SKEL)/%.skel.h: $(OUT)/%.bpf.o
	@mkdir -p $(dir $@)
	$(BPFTOOL) gen skeleton $< > $@

clean:
	rm -rf $(OUT) $(SKEL)

-include $(DEPS)
