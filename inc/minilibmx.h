#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "hero.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

#define FPS 120
#define FRAME_TARGET_TIME (1000 / FPS)

int initialize_window(void);
void setup(void);
void process_input(void);
void update(void);
void render(void);
void destroy_window(void);

SDL_Texture *loadTexture(char *filename);

extern int game_is_running; // = 0
extern SDL_Window *window; //NULL
extern SDL_Renderer *renderer; //NULL
extern int last_frame_time;

struct s_hero {
  float x;
  float y;
  float width;
  float height;
  float xspeed;
  float yspeed;
  unsigned int last_shoot_time;
  unsigned int reload_time;
  SDL_Point lastDirection;
};
extern struct s_hero hero;

struct s_bullet {
  float x;
  float y;
  float width;
  float height;
  SDL_FPoint direction;
  float speed;
  unsigned int lifetime;
  unsigned int create_time;
  struct s_bullet* next_bullet;
  struct s_bullet* previous_bullet;
};
extern struct s_bullet* bullets_list;

#endif
