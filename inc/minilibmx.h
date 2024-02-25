#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int game_is_running = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int initialize_window(void);
void setup();
void process_input();
void update();
void render();
void destroy_window();

struct rectangle {
  float x;
  float y;
  float width;
  float height;
} rectangle;
