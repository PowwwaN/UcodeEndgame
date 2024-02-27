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
  float xspeed;
  float yspeed;
  unsigned int last_shoot_time;
  unsigned int reload_time;
  SDL_Point lastDirection;
} Hero;
extern Hero hero;

struct s_bullet {
  float x;
  float y;
  float width;
  float height;
  SDL_Point direction;
  float speed;
  unsigned int lifetime;
  unsigned int create_time;
  struct s_bullet* next_bullet;
  struct s_bullet* previous_bullet;
};
extern struct s_bullet* bullets_list;


#define HERO_SPEED 150

#endif
