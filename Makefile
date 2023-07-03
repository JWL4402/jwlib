# This Makefile requires Unix. If using on Windows, run in a Git BASH terminal.

CC:=gcc
CFLAGS:=-Wall -Wextra -pedantic
RM:=rm -r

SRC:=src
OBJ:=obj
INCLUDE:=include

SOURCES:=$(wildcard $(SRC)/*.c $(SRC)/*/*.c)
OBJECTS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES))
OBJDIRS:=$(dir $(OBJECTS))
HEADERS:=$(wildcard $(INCLUDE)/*.h $(INCLUDE)/*/*.h)

BUILD:=lib
LIB_NAME=jwlib
LIB_DIR=$(BUILD)\$(LIB_NAME)
LIB=$(LIB_DIR)\lib$(LIB_NAME).a


build: $(LIB) #test

clean:
	$(RM) $(BUILD) $(OBJ)
# Deletes all compiled files.

test: test.o $(LIB)
	gcc -o test $^
	./test
# TODO, when tests are implemented

test.o: tests/test_list.c
	gcc -c $< -o $@


$(LIB): $(LIB_DIR) $(INCLUDE) $(OBJ) $(OBJECTS)
	ar rcs $@ $(OBJECTS)
# compiles object files into the library file

$(LIB_DIR):
	mkdir -p $@
# Creates the library direcrtory

$(INCLUDE): $(HEADERS)
	rsync -rupE $@ $(LIB_DIR)
# Copies the include folder into the lib directory
# TODO : maybe make it so its $(INCLUDE)/$(LIB_NAME)/%.h instead?

$(OBJ): $(OBJDIRS)
	mkdir -p $@
# Makes the object directory

$(OBJDIRS):
	mkdir -p $@
# Makes all object subdirectories

$(OBJ)/%.o: $(SRC)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@
# Compiles the .c files in SRC to .o files in OBJ