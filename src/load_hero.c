#include "../inc/minilibmx.h"

void load_hero() {
  while (true) {
    //////////////////////////////////////////////////////////////////////////////
    /// draw hero
    //////////////////////////////////////////////////////////////////////////////
    // Update animation frame
    currentFrame = (currentFrame + 1) % NUM_FRAMES;

    // Draw character
    SDL_Rect hero_rect = {currentFrame * hero.width,
                          hero.direction * hero.height, hero.width,
                          hero.height};
    SDL_Rect destRect = {hero.x, hero.y, hero.width, hero.height};
    SDL_RenderCopy(renderer, hero_sheet, &hero_rect, &destRect);
    SDL_Delay(100);
    //////////////////////////////////////////////////////////////////////////////
    /// draw hero
    //////////////////////////////////////////////////////////////////////////////
  }
}
