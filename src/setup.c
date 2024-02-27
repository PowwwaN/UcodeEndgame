#include "../inc/minilibmx.h"



void setup() {
  hero.x = 500;      // positition of rectangle by x axis
  hero.y = 500;      // positition of rectangle by y axis
  hero.width = 100;  // width of rectangle
  hero.height = 100; // height of rectangle
  hero.xspeed = 0;
  hero.yspeed = 0;
  hero.last_shoot_time =0;
  hero.reload_time = 500;

  bullets_list = NULL;
  
}

void render() {
  // RGB and opacity
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Background
  SDL_RenderClear(renderer);

  SDL_Rect hero_rect = {hero.x, hero.y, hero.width, hero.height};

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200); // color of a rectangle
  SDL_RenderFillRect(
      renderer,
      &hero_rect); // fills rectangle with predefined size and position

  // rendering bullets

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200); // color of a rectangle
  struct s_bullet* bullet = bullets_list;
  for(;bullet!=NULL;){
    SDL_Rect bullet_rect = {bullet->x, bullet->y, bullet->width, bullet->height};
    SDL_RenderFillRect(
        renderer,
        &bullet_rect);
    bullet = bullet->next_bullet;
  }
  SDL_RenderPresent(renderer); // shows renderer
}

void update() {
  // sleep until reach the target frametime (required only if fps capping
  // needed)
  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait);
  }

  // Get a delta time time factor converted to seconds to be used to update my
  // objects later.
  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

  // logic to keep a fixed timestep
  last_frame_time = SDL_GetTicks();

  
  // hero movement
  hero_movement();
  
  hero.x -= hero.xspeed * delta_time;
  hero.y -= hero.yspeed * delta_time;
   
  bullets();

}