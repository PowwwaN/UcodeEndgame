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

void draw_sprite(SDL_Texture* sprite_sheet, int current_frame, int sprite_direction, int sprite_x, int sprite_y, int sprite_width, int sprite_height, SDL_Renderer* renderer) {
    // Calculate elapsed time since last frame update
    static Uint32 last_frame_time = 0;
    Uint32 current_frame_time = SDL_GetTicks();
    Uint32 elapsed_time = current_frame_time - last_frame_time;

    // Check if it's time to update the frame based on frame rate
    if (elapsed_time >= (1000 / 12)) {
        // Update animation frame
        current_frame = (current_frame + 1) % NUM_FRAMES;
        last_frame_time = current_frame_time; // Update last frame time
    }

    // Uncomment the following lines if you want to draw a hitbox around the sprite
    // SDL_Rect sprite_hitbox = {sprite_x, sprite_y, sprite_width, sprite_height};
    // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200); // color of a rectangle
    // SDL_RenderFillRect(renderer, &sprite_hitbox);

    // Draw sprite
    SDL_Rect sprite_rect = {current_frame * sprite_width, sprite_direction * sprite_height, sprite_width, sprite_height};
    SDL_Rect dest_rect = {sprite_x, sprite_y, sprite_width, sprite_height};
    SDL_RenderCopy(renderer, sprite_sheet, &sprite_rect, &dest_rect);
}
