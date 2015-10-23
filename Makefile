CC ?= cc
CFLAGS ?= -O2 -fPIC -std=gnu99 -Wall -Wextra -pedantic
CPPFLAGS ?=
LDFLAGS ?= -shared

LOCALCFLAGS ?=
LOCALCPPFLAGS ?=
LOCALLDFLAGS ?=

OUTPUT = rualloc.so
SOURCES = rualloc.c

all: $(OUTPUT)

raw:
	$(MAKE) LOCALCPPFLAGS="-DRAW_SYSCALLS -include syscalls_$(PLATFORM).h" LOCALCFLAGS="-nostdlib"

clean:
	rm -f $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) $(LOCALCFLAGS) $(CPPFLAGS) $(LOCALCPPFLAGS) $(LDFLAGS) $(LOCALLDFLAGS) -o $@ $^

.PHONY: all clean raw
