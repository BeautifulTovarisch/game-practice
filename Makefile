# -*- Makefile -*-

SRC := $(wildcard src/**/*.c src/util/**/*.c)
OBJ := $(SRC:.c=.o)

SUBDIRS := $(wildcard src/*/. src/util/*/.)

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

all: main $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

main: src/main.o $(SUBDIRS)
	gcc src/main.o $(OBJ) $(CFLAGS) -o main

.PHONY: clean $(SUBDIRS)
clean:
	rm -f src/main src/main.o

# Recurse into each subdir and execute make clean
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
