NAME = game
CC = clang
CFLAGS = -Wall -std=c99
LIBS = -L/opt/homebrew/Cellar/sdl2/2.30.0/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer -L/opt/homebrew/Cellar/sdl2_image/2.8.2/lib -lSDL2_image -lm

# Specify include directories for SDL2 and SDL2_image headers
INC_DIR = /opt/homebrew/Cellar/sdl2/2.30.0/include
IMG_INC_DIR = /opt/homebrew/Cellar/sdl2_image/2.8.2/include

# Make sure to include the correct directories for SDL2 and SDL2_image headers
INCS = -I$(INC_DIR) -I$(IMG_INC_DIR)

SRC_DIR = src/
OBJ_DIR = obj/

# Use wildcard to gather the list of source files
SRCS = $(wildcard $(SRC_DIR)*.c)
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

all: $(NAME)

# Rule to create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to compile each source file into object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Rule to link object files into the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	rm -rf $(OBJ_DIR)
	
run: $(NAME)
	./$(NAME)

# Clean rule
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(OBJS) $(NAME)

# PHONY rule to avoid conflicts with filenames
.PHONY: all clean run
