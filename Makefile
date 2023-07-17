# This Makefile requires Unix. If using on Windows, run in a Git BASH terminal.

# Flags and commands
CC:=gcc
CFLAGS:=-W -Wall -Wextra -pedantic -pass-exit-codes
RM:=rm -r

# Directories
SRC:=src
OBJ:=obj
INCLUDE:=include
TEST:=tests

# Files
SOURCES:=$(wildcard $(SRC)/*.c $(SRC)/*/*.c)
OBJECTS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES))
OBJDIRS:=$(dir $(OBJECTS))
HEADERS:=$(wildcard $(INCLUDE)/*.h $(INCLUDE)/*/*.h)
TESTS:=$(wildcard $(TEST)/*.c $(TEST)/*/*.c)
TESTEXE:=$(patsubst %.c,%.exe,$(TESTS))
#TESTDIRS:=(dir $(TESTS)) unnecessary, all dirs already exist

BUILD:=lib
LIB_NAME=jwlib
LIB_DIR=$(BUILD)/$(LIB_NAME)
LIB=$(LIB_DIR)/lib$(LIB_NAME).a


build: $(LIB)
test: $(TEST)

clean:
	$(RM) $(BUILD) $(OBJ) $(TESTEXE)
# Deletes all compiled files.


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


$(TEST): $(LIB) $(TESTEXE)
	mkdir -p $@
# Makes the test directory if it doesn't already exist

$(TEST)/%.exe: $(TEST)/%.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $@
	$@
# Compiles and executes all test files.

.PHONY: clean