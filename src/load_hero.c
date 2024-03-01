#include "../inc/minilibmx.h"

void load_hero() {
 for (int i = 0; i <= 1000; i++){
    //////////////////////////////////////////////////////////////////////////////
    /// draw hero
    //////////////////////////////////////////////////////////////////////////////
    // Update animation frame
    currentFrame = (currentFrame + 1) % NUM_FRAMES;
    SDL_Rect hero_hitbox = {hero.x, hero.y, hero.width, hero.height};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200); // color of a rectangle
    SDL_RenderFillRect(
      renderer,
      &hero_hitbox);
    // Draw character
    SDL_Rect hero_rect = {currentFrame * 85,
                          hero.direction * 87, hero.width + 38,
                          hero.height + 9};
    SDL_Rect destRect = {hero.x - 12, hero.y - 10, hero.width + 38, hero.height + 9};
    SDL_RenderCopy(renderer, hero_sheet, &hero_rect, &destRect);
    /////////
    
      //////////
  //  SDL_Delay(100);
    //////////////////////////////////////////////////////////////////////////////
    /// draw hero
    //////////////////////////////////////////////////////////////////////////////
 }
}