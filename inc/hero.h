#ifndef HERO_H
#define HERO_H

#include <SDL2/SDL.h>

typedef struct {
	int x;
	int y;
	SDL_Texture *texture;
} Entity;

typedef struct s_hero {
  float x;
  float y;
  float width;
  float height;
  SDL_Texture *texture;
  float xspeed;
  float yspeed;
  unsigned int last_shoot_time;
  unsigned int reload_time;
  SDL_Point shoot_direction;
} Hero;
extern Hero hero;


SDL_Texture *loadTexture(char *filename);
void blit(SDL_Texture *texture, int x, int y);

#define HERO_SPEED 450
#define HERO_WIDTH 47
#define HERO_HEIGHT 78

#endif
