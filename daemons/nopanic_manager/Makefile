# nopanic_manager Makefile

CC ?= gcc

INCLUDES := -I include \
            -I ../../common/include \
            -I ../../bpf/skel \
            -I ../../bpf/include \
            -I ../../third_party

CFLAGS := -O2 -Wall -Wextra -std=gnu11 $(INCLUDES)

CFLAGS += -DVERSION='"$(VERSION)"' \
          -DBUILD_TIMESTAMP='"$(BUILD_TIMESTAMP)"'

COMMON_LIB := ../../build/common/libcommon.a
VENDOR_LIB := ../../build/third_party/libvendor.a

LIBBPF_DIR ?= /usr/lib64
LDFLAGS := -L$(LIBBPF_DIR) \
           -L../../build/common \
           -L../../build/third_party

LDLIBS := -lcommon -lvendor -lbpf -lelf -lz -lzstd -lpthread

OUT := ../../build/daemons/nopanic_manager
BIN := $(OUT)/nopanic_manager

SRCS := $(shell find src -name '*.c')
OBJS := $(patsubst src/%.c,$(OUT)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: $(BIN)

$(OBJS): $(OUT)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -MF $(OUT)/$*.d -c $< -o $@

$(BIN): $(OBJS) $(COMMON_LIB) $(VENDOR_LIB)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf $(OUT)

-include $(DEPS)