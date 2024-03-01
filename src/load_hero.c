#include "../inc/minilibmx.h"

void load_hero() {
  // Calculate elapsed time since last frame update
  static Uint32 lastFrameTime = 0;
  Uint32 currentFrameTime = SDL_GetTicks();
  Uint32 elapsedTime = currentFrameTime - lastFrameTime;

  // Check if it's time to update the frame based on frame rate
  if (elapsedTime >= (1000 / 12)) {
    // Update animation frame
    currentFrame = (currentFrame + 1) % NUM_FRAMES;
    lastFrameTime = currentFrameTime; // Update last frame time
  }
  //////////////////////////////////////////////////////////////////////////////
  /// draw hero
  //////////////////////////////////////////////////////////////////////////////

  // Draw character
  SDL_Rect hero_rect = {currentFrame * 85, hero.direction * 87, hero.width + 38,
                        hero.height + 9};
  SDL_Rect destRect = {hero.x - 12, hero.y - 10, hero.width + 38,
                       hero.height + 9};
  SDL_RenderCopy(renderer, hero_sheet, &hero_rect, &destRect);

  //////////////////////////////////////////////////////////////////////////////
  /// draw hero
  //////////////////////////////////////////////////////////////////////////////
}

void draw_idle() {
  // Calculate elapsed time since last frame update
  static Uint32 lastFrameTimeidle = 0;
  Uint32 currentFrameTimeidle = SDL_GetTicks();
  Uint32 elapsedTimeidle = currentFrameTimeidle - lastFrameTimeidle;

  // Check if it's time to update the frame based on frame rate
  if (elapsedTimeidle >= (1000 / 12)) {
    // Update animation frame
    currentFrame_x = (currentFrame_x + 1) % NUM_FRAMES_IDLE;
    lastFrameTimeidle = currentFrameTimeidle; // Update last frame time
  }
  //////////////////////////////////////////////////////////////////////////////
  /// draw hero
  //////////////////////////////////////////////////////////////////////////////

  // Draw character
  SDL_Rect idle_rect = {currentFrame_x * 70, 0, 70, 100};
  SDL_Rect destRectidle = {hero.x - 12, hero.y - 10, 70, 100};
  SDL_RenderCopy(renderer, idle_sheet, &idle_rect, &destRectidle);

  //////////////////////////////////////////////////////////////////////////////
  /// draw hero
  //////////////////////////////////////////////////////////////////////////////
}
