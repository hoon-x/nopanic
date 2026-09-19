# Common Makefile

CC ?= gcc
AR ?= ar

INCLUDES := -I include \
            -I ../third_party

CFLAGS := -O2 -Wall -Wextra -std=gnu11 -fPIC $(INCLUDES)

OUT := ../build/common

SRCS := $(shell find src -name '*.c')
OBJS := $(patsubst src/%.c,$(OUT)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

LIB := $(OUT)/libcommon.a

VENDOR_LIB := ../build/third_party/libvendor.a

.PHONY: all clean

all: $(LIB)

$(OBJS): $(OUT)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -MF $(OUT)/$*.d -c $< -o $@

$(LIB): $(OBJS) $(VENDOR_LIB)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $(OBJS)

clean:
	rm -rf $(OUT)

-include $(DEPS)