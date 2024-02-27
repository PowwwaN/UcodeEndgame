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
#include "hero.h"
#include "enemy.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

#define FPS 120
#define FRAME_TARGET_TIME (1000 / FPS)

#define MAX_ENEMIES 5

//typedef struct s_hero {
//    float x;
//    float y;
//    float width;
//    float height;
//    float xspeed;
//    float yspeed;
//} Hero;
//extern Hero hero;

extern SDL_Window *window;
extern SDL_Renderer *renderer;


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



#endif