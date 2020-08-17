# -*- Makefile -*-

SRC := $(wildcard src/**/*.c)
OBJ := $(SRC:.c=.o)

SUBDIRS := $(wildcard src/*/.)

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

all: main $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

main: src/main.o $(SUBDIRS) queue
	gcc src/main.o $(OBJ) \
	src/util/queue/mod.o \
	$(CFLAGS) -o main

queue:
	$(MAKE) -C src/util/queue

.PHONY: clean $(SUBDIRS) queue
clean:
	rm -f src/main src/main.o
	rm -f src/util/queue/mod src/util/queue/mod.o

# Recurse into each subdir and execute make clean
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
