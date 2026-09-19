# Root Makefile

SHELL := /bin/bash

VERSION := 1.0.0
BUILD_TIMESTAMP := $(shell date '+%Y-%m-%d %H:%M:%S')
export VERSION
export BUILD_TIMESTAMP

OS_TAG := $(shell . /etc/os-release 2>/dev/null && \
            echo "$${ID}$${VERSION_ID%%.*}" || echo "unknown")
DATE := $(shell date +%Y%m%d)

PKG_NAME  := nopanic_$(OS_TAG)_$(VERSION)_$(DATE)
STAGE_DIR := build/pkg/$(PKG_NAME)
TARBALL   := build/$(PKG_NAME).tar.gz

## daemons/ 하위에서 자기 Makefile을 가진 디렉터리만 탐지
DAEMON_NAMES := $(notdir $(patsubst %/,%,$(dir $(wildcard daemons/*/Makefile))))

DAEMON_TARGETS := $(addprefix daemon-,$(DAEMON_NAMES))
CLEAN_DAEMON_TARGETS := $(addprefix clean-daemon-,$(DAEMON_NAMES))

.PHONY: all bpf third_party common daemons clean stage package \
    $(DAEMON_TARGETS) $(CLEAN_DAEMON_TARGETS)

all: package

bpf:
	$(MAKE) -C bpf all

third_party:
	$(MAKE) -C third_party all

common: bpf third_party
	$(MAKE) -C common all

daemons: common $(DAEMON_TARGETS)

$(DAEMON_TARGETS): daemon-%:
	$(MAKE) -C daemons/$* all

stage: daemons
	rm -rf $(STAGE_DIR)
	install -d $(STAGE_DIR)/var
	install -d $(STAGE_DIR)/config
	install -d $(STAGE_DIR)/doc
	install -d $(STAGE_DIR)/doc/licenses
	@for d in $(DAEMON_NAMES); do \
		install -m 0755 build/daemons/$$d/$$d $(STAGE_DIR)/; \
		if [ -d daemons/$$d/config ]; then \
			cp -r daemons/$$d/config/. $(STAGE_DIR)/config/; \
		fi; \
	done
	install -m 0644 README.md LICENSE NOTICE $(STAGE_DIR)/doc/
	install -m 0644 third_party/licenses/*.LICENSE $(STAGE_DIR)/doc/licenses/

package: stage
	tar -C build/pkg -czf $(TARBALL) $(PKG_NAME)
	@echo ">> $(TARBALL)"

$(CLEAN_DAEMON_TARGETS): clean-daemon-%:
	$(MAKE) -C daemons/$* clean

clean: $(CLEAN_DAEMON_TARGETS)
	$(MAKE) -C common clean
	$(MAKE) -C bpf clean
	$(MAKE) -C third_party clean
	rm -rf build