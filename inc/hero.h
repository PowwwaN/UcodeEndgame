#ifndef HERO_H
#define HERO_H

#include <SDL2/SDL.h>

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
  int hp;
  bool active;
  bool attacked;
} Hero;
extern Hero hero;


SDL_Texture *loadTexture(char *filename);
void blit(SDL_Texture *texture, int x, int y);
#define HERO_SPEED 450
#define HERO_WIDTH 47
#define HERO_HEIGHT 78
#define REPULSION_DISTANCE 30
#define M_PI 3.14159265358979323846

#endif // HERO_H
