HOST_CC ?= cc
AMIGA_CC ?= m68k-amigaos-gcc
CFLAGS ?= -std=c89 -Wall -Wextra -Werror -pedantic -Iinclude -Isrc
AMIGA_CFLAGS ?= -m68000 -Os -std=c89 -Wall -Wextra -Iinclude -Isrc

HOST_TEST = build/test_protocol
AMIGA_BIN = build/AmiMQTT

.PHONY: all check host-test amiga clean

all: host-test

build:
	mkdir -p build

$(HOST_TEST): build tests/test_protocol.c src/protocol/protocol.c src/protocol/protocol.h
	$(HOST_CC) $(CFLAGS) -o $@ tests/test_protocol.c src/protocol/protocol.c

host-test: $(HOST_TEST)
	./$(HOST_TEST)

check: host-test
	python3 tools/check_m1.py

amiga: build
	$(AMIGA_CC) $(AMIGA_CFLAGS) -o $(AMIGA_BIN) src/main.c src/protocol/protocol.c

clean:
	rm -rf build
