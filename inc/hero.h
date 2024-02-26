#ifndef HERO_H
#define HERO_H

#include <SDL2/SDL.h>

typedef struct s_hero {
    float x;
    float y;
    float width;
    float height;
    float xspeed;
    float yspeed;
} Hero;
extern Hero hero;

//typedef struct {
//    int x;
//    int y;
//    SDL_Texture *texture;
//} Entity;

#endif