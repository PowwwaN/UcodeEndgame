#include "minilibmx.h"
#include <SDL2/SDL_render.h>

void render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_Rect rectangle_rect = {rectangle.x, rectangle.y, rectangle.width,
                             rectangle.height};

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &rectangle_rect);

  SDL_RenderPresent(renderer);
}

void update() {
  // todo
}
