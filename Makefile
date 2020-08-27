# -*- Makefile -*-

SRC := $(wildcard src/**/mod.c src/util/**/mod.c)
OBJ := $(SRC:.c=.o)

TEST := $(wildcard src/*/test.c src/util/**/test.c)

SUBDIRS := $(wildcard src/*/. src/util/*/.)

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

all: main $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

main: src/main.o $(SUBDIRS)
	gcc src/main.o $(OBJ) $(CFLAGS) -o main

test: $(SUBDIRS)
	gcc $(TEST) $(OBJ) $(CFLAGS) -l cmocka -o test
	CMOCKA_MESSAGE_OUTPUT=tap ./test
	rm -f test

.PHONY: test clean $(SUBDIRS)
clean:
	rm -f src/main src/main.o

# Recurse into each subdir and execute make clean
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
