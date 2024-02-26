all:
	gcc -Wall -std=c99 ./src/*.c ./inc/*.h `sdl2-config --libs --cflags` -lm -o game

run:
	./game
	
# Clean rule
rm:
	rm game

# PHONY rule to avoid conflicts with filenames
.PHONY: all clean test
