#include "../inc/minilibmx.h"


void load_hero(int action, int numFrames) {
  // Calculate elapsed time since last frame update
  static Uint32 last_frame_time = 0;
  Uint32 current_frame_time = SDL_GetTicks();
  Uint32 elapsed_time = current_frame_time - last_frame_time;

  // Check if it's time to update the frame based on frame rate
  if (elapsed_time >= (1000 / 12)) {
    // Update animation frame
    current_frame = (current_frame + 1) % numFrames;
    last_frame_time = current_frame_time; // Update last frame time
  }
  //////////////////////////////////////////////////////////////////////////////
  /// draw hero
  //////////////////////////////////////////////////////////////////////////////

  // Draw character
  if (action == 0) {
    // Render idle animation
    SDL_Rect idle_rect = {current_frame * 70, 0, 70, 100}; // вирізає картинку, трогати не можна
    SDL_Rect dest_rect_idle = {hero.x - 12, hero.y - 10, 70, 100};
    SDL_RenderCopy(renderer, idle_sheet, &idle_rect, &dest_rect_idle);

    // Draw hitbox around the hero
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for hitbox
    // SDL_Rect hitbox_rect = {hero.x - 12, hero.y - 10, 70, 100}; // Adjust dimensions as needed
    // SDL_RenderDrawRect(renderer, &hitbox_rect);
} else if (action == 1) {
    // Render hero movement animation
    SDL_Rect hero_rect = {current_frame * 85, hero.direction * 87, hero.width + 38, hero.height + 9};
    SDL_Rect dest_rect = {hero.x - 12, hero.y - 10, hero.width + 38, hero.height + 9};
    SDL_RenderCopy(renderer, hero_sheet, &hero_rect, &dest_rect);

    // Draw hitbox around the hero
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for hitbox
    // SDL_Rect hitbox_rect = {hero.x - 12, hero.y - 10, hero.width + 38, hero.height + 9}; // Adjust dimensions as needed
    // SDL_RenderDrawRect(renderer, &hitbox_rect);
} 
//////////////////////////////////////////////////////////
  /// draw hero
  //////////////////////////////////////////////////////////////////////////////
}

void load_enemy(int action, int numFrames, int x, int y) {
  // Calculate elapsed time since last frame update
  static Uint32 last_frame_time = 0;
  Uint32 current_frame_time = SDL_GetTicks();
  Uint32 elapsed_time = current_frame_time - last_frame_time;

  // Check if it's time to update the frame based on frame rate
  if (elapsed_time >= (1000 / 12)) {
    // Update animation frame
    current_frame = (current_frame + 1) % numFrames;
    last_frame_time = current_frame_time; // Update last frame time
  }
  //////////////////////////////////////////////////////////////////////////////
  /// draw enemy
  //////////////////////////////////////////////////////////////////////////////

  if (action == 2) {
    SDL_Rect enemy_rect = {current_frame * 64, 0, 64, 64}; // Adjust dimensions and sprite sheet as needed
    SDL_Rect dest_rect_enemy = {x, y, 64, 64};
    SDL_RenderCopy(renderer, enemy_sheet1, &enemy_rect, &dest_rect_enemy);

    // Draw hitbox around the hero
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for hitbox
    // SDL_Rect hitbox_rect = {x, y, 64, 64}; // Adjust dimensions as needed
    // SDL_RenderDrawRect(renderer, &hitbox_rect);
  } if (action == 3) {
    SDL_Rect enemy_rect = {current_frame * 64, 0, 64, 64}; // Adjust dimensions and sprite sheet as needed
    SDL_Rect dest_rect_enemy = {x, y, 64, 64};
    SDL_RenderCopy(renderer, enemy_sheet2, &enemy_rect, &dest_rect_enemy);

     // Draw hitbox around the hero
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for hitbox
    // SDL_Rect hitbox_rect = {x, y, 64, 64}; // Adjust dimensions as needed
    // SDL_RenderDrawRect(renderer, &hitbox_rect);
  } if (action == 4) {
    SDL_Rect enemy_rect = {current_frame * 64, 0, 64, 64}; // Adjust dimensions and sprite sheet as needed
    SDL_Rect dest_rect_enemy = {x, y, 64, 64};
    SDL_RenderCopy(renderer, enemy_sheet3, &enemy_rect, &dest_rect_enemy);

     // Draw hitbox around the hero
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for hitbox
    // SDL_Rect hitbox_rect = {x, y, 64, 64}; // Adjust dimensions as needed
    // SDL_RenderDrawRect(renderer, &hitbox_rect);
  }
}
