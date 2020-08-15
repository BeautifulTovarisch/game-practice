# -*- Makefile -*-

SRC := $(wildcard src/*.c)
OBJ := $(wildcard SRC:.c=.o)

SUBDIRS := $(wildcard src/*/.)

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

all: main $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

main: src/main.o $(SUBDIRS)
	gcc src/main.o $(OBJ) $(CFLAGS) -o main

.PHONY: clean $(SUBDIRS)
clean:
	rm -f src/main src/main.o

	$(MAKE) clean -C $(SUBDIRS)
