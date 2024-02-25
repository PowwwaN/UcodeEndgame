#include "minilibmx.h"

void destroy_window(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

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
