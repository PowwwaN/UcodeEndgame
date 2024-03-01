#include "../inc/minilibmx.h"


void load_hero(int action, int numFrames) {
  // Calculate elapsed time since last frame update
  static Uint32 lastFrameTime = 0;
  Uint32 currentFrameTime = SDL_GetTicks();
  Uint32 elapsedTime = currentFrameTime - lastFrameTime;

  // Check if it's time to update the frame based on frame rate
  if (elapsedTime >= (1000 / 12)) {
    // Update animation frame
    currentFrame = (currentFrame + 1) % numFrames;
    lastFrameTime = currentFrameTime; // Update last frame time
  }
  //////////////////////////////////////////////////////////////////////////////
  /// draw hero
  //////////////////////////////////////////////////////////////////////////////

  // Draw character
  if (action == 0) {
    // Render idle animation
    SDL_Rect idle_rect = {currentFrame * 70, 0, 70, 100};
    SDL_Rect destRect_idle = {hero.x - 12, hero.y - 10, 70, 100};
    SDL_RenderCopy(renderer, idle_sheet, &idle_rect, &destRect_idle);

    // Draw hitbox around the hero
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for hitbox
    // SDL_Rect hitbox_rect = {hero.x - 12, hero.y - 10, 70, 100}; // Adjust dimensions as needed
    // SDL_RenderDrawRect(renderer, &hitbox_rect);
} else if (action == 1) {
    // Render hero movement animation
    SDL_Rect hero_rect = {currentFrame * 85, hero.direction * 87, hero.width + 38, hero.height + 9};
    SDL_Rect destRect = {hero.x - 12, hero.y - 10, hero.width + 38, hero.height + 9};
    SDL_RenderCopy(renderer, hero_sheet, &hero_rect, &destRect);

    // Draw hitbox around the hero
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for hitbox
    // SDL_Rect hitbox_rect = {hero.x - 12, hero.y - 10, hero.width + 38, hero.height + 9}; // Adjust dimensions as needed
    // SDL_RenderDrawRect(renderer, &hitbox_rect);
}
//////////////////////////////////////////////////////////
  /// draw hero
  //////////////////////////////////////////////////////////////////////////////
}
