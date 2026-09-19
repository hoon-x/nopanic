# Third Party Makefile

CC ?= gcc
AR ?= ar

## 업스트림 코드라 우리 경고 정책(-Wall -Wextra)을 강제하지 않음
CFLAGS := -O2 -fPIC

OUT := ../build/third_party
LIB := $(OUT)/libvendor.a

SRCS := cjson/cJSON.c picohttpparser/picohttpparser.c
OBJS := $(patsubst %.c,$(OUT)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: $(LIB)

$(OBJS): $(OUT)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -MF $(OUT)/$*.d -c $< -o $@

$(LIB): $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

clean:
	rm -rf $(OUT)

-include $(DEPS)s
