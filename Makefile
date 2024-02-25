CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

SRCDIR = src
INCDIR = inc
BINDIR = bin

EXECUTABLE = $(BINDIR)/game

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BINDIR)/%.o: $(SRCDIR)/%.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(BINDIR)/*.o $(EXECUTABLE)
