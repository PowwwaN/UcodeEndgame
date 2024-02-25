#include "./constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int game_is_running = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return 0;
  }
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
  if (!window) {
    fprintf(stderr, "Error creating SDL Window.\n");
    return 0;
  }
  renderer = SDL_CreateRenderer(
      window, 0 /*devices, driver, etc. -1 means default*/, 0 /*flags*/);
  if (!renderer) {
    fprintf(stderr, "Error creating SDL Renderer\n");
    return 0;
  }
  return 1;
}

void setup(){
  //todo
}

void process_input(){
  SDL_Event event;
  SDL_PollEvent(&event);

  switch(event.type){
    case SDL_QUIT:
      game_is_running = 0;
      break;
    case SDL_KEYDOWN:
      if(event.key.keysym.sym == SDLK_ESCAPE)
        game_is_running = 0;
      break;
  }
}

void update(){
//todo
}

void render(){
  SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
}

void destroy_window(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  game_is_running = initialize_window();

  setup();

  while (game_is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  return 0;
}
