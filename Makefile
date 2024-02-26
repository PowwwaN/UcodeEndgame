NAME = -o game

CC = gcc
CFLAGS = -Wall -std=c99 
LIBS = -lSDL2 -lm

SRC_DIR = src/
INC_DIR = inc/

SRCS = $(SRC_DIR)*.c
INCS = $(INC_DIR)*.h
all:
	$(CC) $(CFLAGS) $(SRCS) $(INCS) $(LIBS) $(NAME)

run:
	./game
	
# Clean rule
clean:
	rm game

# PHONY rule to avoid conflicts with filenames
.PHONY: all clean test
