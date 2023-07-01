# This Makefile requires Unix. If using on Windows, run in a Git BASH terminal.

CC=gcc
CFLAGS=-c -Wall -Wextra -pedantic

SOURCES=$(wildcard src/*.c src/*/*.c)
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(wildcard include/*.h include/*/*.h)

LIB_NAME=jwlib
LIB_DIR=build\$(LIB_NAME)
LIB_INCLUDES=$(LIB_DIR)
LIB=$(LIB_DIR)\lib$(LIB_NAME).a

all: $(LIB_DIR) includes $(LIB) $(SOURCES)

$(LIB_DIR):
	mkdir -p $@
# this requires unix lmao . use git bash not cmd

includes: $(HEADERS)
	rsync -rupE include $(LIB_INCLUDES)
# copies include folder into library folder

$(LIB): $(OBJECTS)
	ar rcs $(LIB) $(OBJECTS)
# compiles object files into the library file

.c.o:
	$(CC) $(CFLAGS) $< -o $@
# compiles c files into object files