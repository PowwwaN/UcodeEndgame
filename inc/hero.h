#ifndef HERO_H
#define HERO_H

#include <SDL2/SDL.h>

typedef struct {
	int x;
	int y;
	SDL_Texture *texture;
} Entity;

#endif
