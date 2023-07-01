CC=gcc
CFLAGS=-c -Wall

SOURCES=$(wildcard */*/*.c)
OBJECTS=$(SOURCES:.c=.o)

INCLUDES_SRC=$(wildcard include/*/*.h)
HEADERS=$(patsubst include/%, %, $(INCLUDES_SRC))

LIB_NAME=jwlib
LIB_DIR=build\$(LIB_NAME)
LIB=$(LIB_DIR)\lib$(LIB_NAME).a

all: $(LIB_DIR) $(LIB) $(SOURCES)

$(LIB_DIR):
	mkdir -p $@
# this requires unix lmao . use git bash not cmd

$(LIB): $(OBJECTS)
	ar rcs $(LIB) $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@
