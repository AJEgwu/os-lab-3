CC      = gcc
CFLAGS  = -Wall -Wextra -std=gnu11 -O2 -g
BINDIR  = bin

SRC_DIRS = src challenges

SRCS := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
PROGS_SRC := $(SRCS)
PROGS_BIN := $(patsubst src/%.c,$(BINDIR)/%,$(filter src/%.c,$(PROGS_SRC))) \
             $(patsubst challenges/%.c,$(BINDIR)/%,$(filter challenges/%.c,$(PROGS_SRC)))

all: $(BINDIR) $(PROGS_BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: src/%.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR)/%: challenges/%.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BINDIR)
