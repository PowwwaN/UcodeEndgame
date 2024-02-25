CC = gcc
CFLAGS = -Wall 
LIBS = -lSDL2

SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

SRCS = $(SRC_DIR)*.c
INCS = $(INC_DIR)*.h
OBJS = $(OBJ_DIR)*.c $(OBJ_DIR)*.h

# Target for compiling all .o files
all:
	mkdir obj
	cp $(SRCS) $(OBJ_DIR)
	cp $(INCS) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o game
	rm -rf obj

# Clean rule
clean:
	rm game

# PHONY rule to avoid conflicts with filenames
.PHONY: all clean test
