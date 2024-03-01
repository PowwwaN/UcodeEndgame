#ifndef HERO_H
#define HERO_H

#include <SDL2/SDL.h>

typedef struct s_hero {
  float x;
  float y;
  float width;
  float height;
  SDL_Texture *texture;
  int direction;// 0: down, 1: down-right, 2: right, 3: up-right, 4: up, 5: up-left, 6: left, 7: down-left
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

extern int currentFrame;
extern SDL_Texture *hero_sheet;

SDL_Texture *loadTexture(char *filename);
void blit(SDL_Texture *texture, int x, int y);
SDL_Texture* loadImage(const char* filename, SDL_Renderer* renderer);
void load_hero();

#define HERO_SPEED 450
#define HERO_WIDTH 85
#define HERO_HEIGHT 87
#define NUM_FRAMES 6
#define REPULSION_DISTANCE 30
#define M_PI 3.14159265358979323846

#endif // HERO_H
