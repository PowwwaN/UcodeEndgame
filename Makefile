NAME = game

CC = clang
CFLAGS = -Wall -std=c99 -g
LIBS = -lSDL2 -lSDL2_image -lm

SRC_DIR = src/
OBJ_DIR = obj/

SRCS = $(wildcard $(SRC_DIR)*.c)
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

all: $(NAME)

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile each source file into object files and move them to obj directory
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
 
# Link object files into the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

	rm -rf obj/
	
rebuild: clean all

run: $(NAME)
	./$(NAME)

# Clean rule
clean:
	rm -f $(NAME) $(OBJS)

# PHONY rule to avoid conflicts with filenames
.PHONY: all clean run test
